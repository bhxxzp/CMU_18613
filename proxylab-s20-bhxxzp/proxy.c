/*
 * Name: Peng Zeng
 * AndrewID: pengzeng
 *
 * Starter code for proxy lab.
 * In the first part of the proxy lab, I implement the web proxy, using double
 * linked list to store the data getting from server. If the data client wants
 * to get is stored in cache, then the proxy can reply the data directly,
 * instead of getting another data from server. Also, the double linked list
 * implement the LRU policy. When a web browser uses a proxy, it contacts the
 * proxy instead of communicating directly with the web server; the proxy
 * forwards the client’s request to the web server, reads the server’s response,
 * then forwards the response to the client. The proxy I created can accepts
 * incoming connections, reads and parses requests, forwards requests to web
 * servers, reads the servers’ responses, and forwards the responses to the
 * corresponding clients. I get the idea from the textbook CSAPP Tiny web
 */

/* Some useful includes to help you get started */

#include "cache.h"
#include "csapp.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
 * Debug macros, which can be enabled by adding -DDEBUG in the Makefile
 * Use these if you find them useful, or delete them if not
 */
#ifdef DEBUG
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_printf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg_assert(...)
#define dbg_printf(...)
#endif

/*
 * Max cache and object sizes
 * You might want to move these to the file containing your cache implementation
 */
#define MAX_CACHE_SIZE (1024 * 1024)
#define MAX_OBJECT_SIZE (100 * 1024)

/*
 * String to use for the User-Agent header.
 * Don't forget to terminate with \r\n
 */
static const char *header_user_agent = "Mozilla/5.0"
                                       " (X11; Linux x86_64; rv:3.10.0)"
                                       " Gecko/20191101 Firefox/63.0.1\r\n";
typedef struct sockaddr SA;
static DLlist *list;
void doit(int fd);
void parse_uri(char *uri, char *host, char *port, char *path);
int Open_listenfd(char *port);
int Accept(int listenfd, struct sockaddr *addr, socklen_t *addrlen);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
                 char *longmsg);
void build_header(rio_t *rio, char *http_header, char *hostname, char *path,
                  char *port, char *uri, char *version);
void *thread(void *vargp);

/*
 * Listen the connection from the port. After opening a listening socket by
 * Open_listenfd function, excutes the server loop, and then repeatedly
 * accepting a connection requesting. After receiving it, calling the doit
 * function to execute it and then close the connection.
 *
 * @argc: The number of the words in a command line
 * @argv: A group pointers pointing at the word in command lines
 *
 */
int main(int argc, char **argv) {
    int listenfd, *connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    /* Ignore the signal SIGPIPE */
    Signal(SIGPIPE, SIG_IGN);

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }

    /* Initialize the cache list */
    list = init_cache();

    /* Open the listenfd to hear from the connection requests */
    listenfd = Open_listenfd(argv[1]);
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Malloc(sizeof(int));
        /* Repeatedly receive the connection requests */
        *connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port,
                    MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        // doit(*connfd);
        pthread_create(&tid, NULL, thread, connfd);
        // close(*connfd);
    }
    free_list(list);
    return 0;
}

void *thread(void *vargp) {
    int connfd = *((int *)vargp);
    pthread_detach(pthread_self());
    Free(vargp);
    doit(connfd);
    close(connfd);
    return NULL;
}

/* Specify my own open_listened to avoid some error */
int Open_listenfd(char *port) {
    int result;
    if ((result = open_listenfd(port)) == -1) {
        printf("Can't open listenfd %s\n", port);
        exit(-1);
    } else {
        return result;
    }
}

int Open_clientfd(char *hostname, char *port) {
    int result;
    if ((result = open_clientfd(hostname, port)) == -1) {
        printf("Can't open clientfd %s\n", port);
        return -1;
    } else {
        return result;
    }
}

/* Specify my own Accept function to avoid some error */
int Accept(int listenfd, struct sockaddr *addr, socklen_t *addrlen) {
    int result;
    if ((result = accept(listenfd, addr, addrlen)) == -1) {
        printf("Can't accept\n");
        exit(-1);
    } else {
        return result;
    }
}

/*
 * Doit function handles the HTTP transaction.
 *
 */
void doit(int fd) {
    rio_t rio, rio_server;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char hostname[MAXLINE], path[MAXLINE], port[MAXLINE], http_header[MAXLINE];
    char buff[MAXLINE];
    bool mask = false;
    int fd_server;
    // int back_info;

    /* Read request line and headers */
    rio_readinitb(&rio, fd);
    rio_readlineb(&rio, buf, MAXLINE);
    printf("Request headers:\n");
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcmp(method, "GET")) {
        clienterror(fd, method, "501", "Not implemented",
                    "Tiny does not imlement this method");
        return;
    }

    /* Parse URI from GET info */
    parse_uri(uri, hostname, port, path);

    size_t node_size = 0;
    char *node_value = get_value(list, uri, &node_size);

    /*cache hit and sent object from cache to client*/
    if (node_value != NULL) {
        rio_writen(fd, node_value, node_size);
        Free(node_value);
        return;
    }

    /* Connect the client with server */
    if ((fd_server = Open_clientfd(hostname, port)) < 0) {
        printf("Can't connect to %s with %s\r\n", hostname, port);
        return;
    }
    /* Associates the descriptor nect with a read buffer */
    rio_readinitb(&rio_server, fd_server);

    /* Send the header to server */
    /* Build the http header */
    build_header(&rio, http_header, hostname, path, port, uri, version);

    rio_writen(fd_server, http_header, strlen(http_header));

    size_t n;
    char temp_value[MAX_OBJECT_SIZE];
    size_t total = 0;

    while ((n = rio_readnb(&rio_server, buff, MAXLINE)) > 0) {
        if ((total + n) <= MAX_OBJECT_SIZE) {
            memcpy(temp_value + total, buff, n);
            total += n;
        } else {
            mask = true;
        }
        rio_writen(fd, buff, n);
    }

    if (mask == false) {
        write_node(list, uri, temp_value, total);
    }

    if (node_value != NULL) {
        Free(node_value);
    }
    close(fd_server);
}

/*
 * The function will read the request headers and extract the hostname, path,
 * port, version to build the http header
 *
 */
void build_header(rio_t *rio, char *http_header, char *hostname, char *path,
                  char *port, char *uri, char *version) {
    char buf[MAXLINE];

    memset(http_header, '\0', MAXLINE);
    sprintf(http_header, "GET http://%s:%s%s %s\r\n", hostname, port, path,
            version);

    char *Connection = "Connection: ";
    char *Host = "Host: ";
    char *User_Agent = "User-Agent: ";
    char *close = "close";
    char *Proxy_Connection = "Proxy-Connection: ";
    char *strColon = ":";
    char *end = "\r\n";

    while (rio_readlineb(rio, buf, MAXLINE) > 0) {
        if (!strcmp(buf, "\r\n")) {
            break;
        }
        /* Build the Connection header */
        else if (!strncasecmp(buf, Connection, strlen(Connection))) {
            memset(buf, '\0', MAXLINE);
            strcat(buf, Connection);
            strcat(buf, close);
            strcat(buf, end);
        }
        /* Build the Host header */
        else if (!strncasecmp(buf, Host, strlen(Host))) {
            memset(buf, '\0', MAXLINE);
            strcat(buf, Host);
            strcat(buf, hostname);
            strcat(buf, strColon);
            strcat(buf, port);
            strcat(buf, end);
        }
        /* Build the User_Agent header */
        else if (!strncasecmp(buf, User_Agent, strlen(User_Agent))) {
            memset(buf, '\0', MAXLINE);
            strcat(buf, User_Agent);
            strcat(buf, header_user_agent);
            strcat(buf, end);
        }
        /* Build the Proxy_Connection header */
        else if (!strncasecmp(buf, Proxy_Connection,
                              strlen(Proxy_Connection))) {
            memset(buf, '\0', MAXLINE);
            strcat(buf, Proxy_Connection);
            strcat(buf, close);
            strcat(buf, end);
        }
        strcat(http_header, buf);
    }
    strcat(http_header, "\r\n");

    /* Write the header to server */
    // rio_writen(fd_connect, http_header, strlen(http_header));
    return;
}

/*
 * Parse the uri into hostname, port and path
 */
void parse_uri(char *uri, char *host, char *port, char *path) {
    char *ptr;
    char *ptrPath;
    char *ptrPort;
    int host_length = 0;
    int port_length = 0;

    memset(host, '\0', MAXLINE);
    memset(port, '\0', MAXLINE);
    memset(path, '\0', MAXLINE);

    /* Extrace the uri */
    if (!!(ptr = strstr(uri, "//"))) {
        ptr += 2;
    } else {
        ptr = uri;
    }

    /* Extrace the file path from the uri */
    ptrPath = strstr(ptr, "/");
    host_length = (int)(ptrPath - ptr);
    memcpy(path, ptrPath, strlen(ptrPath));

    /* Extract the port */
    if (!!(ptrPort = strstr(ptr, ":"))) {
        port_length = (int)(ptrPath - ptrPort - 1);
        strncpy(port, ptrPort + 1, port_length);
        strncpy(host, ptr, host_length - port_length - 1);
    } else { /* Defuat port */
        memcpy(port, "80", strlen("80"));
        strncpy(host, ptr, host_length);
    }
    printf("%s\n %s\n %s\n", host, port, path);

    return;
}

/*
 * Print the Error information
 */
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
                 char *longmsg) {
    char buf[MAXLINE], body[MAXLINE];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Proxy Error</title>");
    sprintf(body,
            "%s<body bgcolor="
            "ffffff"
            ">\r\n",
            body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Proxy Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    rio_writen(fd, buf, strlen(buf));
    rio_writen(fd, body, strlen(body));
}
