#
# Makefile for the CS:APP Shell Lab
#
# Type "make" to build your shell and driver
#
SHELL = /bin/bash
include .labname.mk


# Compiler / linker options
CC = /usr/bin/gcc
CFLAGS = -Wall -g -O2 -Werror -std=gnu99 -D_FORTIFY_SOURCE=2 -I.
LDLIBS = -lpthread


# For tshlab, LLVM is only used for clang-format
LLVM_PATH = /usr/local/depot/llvm-7.0/bin/
ifneq (,$(wildcard /usr/lib/llvm-7/bin/))
  LLVM_PATH = /usr/lib/llvm-7/bin/
endif


# Functions to interpose in wrapper.c
WRAPCFLAGS :=
WRAPCFLAGS += -Wl,--wrap=fork
WRAPCFLAGS += -Wl,--wrap=kill
WRAPCFLAGS += -Wl,--wrap=killpg
WRAPCFLAGS += -Wl,--wrap=waitpid
WRAPCFLAGS += -Wl,--wrap=execve
WRAPCFLAGS += -Wl,--wrap=tcsetpgrp
WRAPCFLAGS += -Wl,--wrap=signal
WRAPCFLAGS += -Wl,--wrap=sigaction
WRAPCFLAGS += -Wl,--wrap=sigsuspend
WRAPCFLAGS += -Wl,--wrap=sigprocmask
WRAPCFLAGS += -Wl,--wrap=printf
WRAPCFLAGS += -Wl,--wrap=fprintf
WRAPCFLAGS += -Wl,--wrap=sprintf
WRAPCFLAGS += -Wl,--wrap=snprintf
WRAPCFLAGS += -Wl,--wrap=init_job_list
WRAPCFLAGS += -Wl,--wrap=job_get_pid
WRAPCFLAGS += -Wl,--wrap=job_set_state


# Auxiliary programs
HELPER_PROGS :=
HELPER_PROGS += myspin1
HELPER_PROGS += myspin2
HELPER_PROGS += myenv
HELPER_PROGS += myintp
HELPER_PROGS += myints
HELPER_PROGS += mytstpp
HELPER_PROGS += mytstps
HELPER_PROGS += mysplit
HELPER_PROGS += mysplitp
HELPER_PROGS += mycat
HELPER_PROGS += mysleepnprint
HELPER_PROGS += mysigfun
HELPER_PROGS += mytstpandspin
HELPER_PROGS += myspinandtstps
HELPER_PROGS += myusleep

# Prefix all helper programs with testprogs/
HELPER_PROGS := $(HELPER_PROGS:%=testprogs/%)


# List all build targets and header files
HANDIN_FILES = tsh.c QUESTIONS.txt
HANDIN_TAR = tshlab-handin.tar

FILES = sdriver runtrace tsh $(HELPER_PROGS) $(HANDIN_TAR)
DEPS = config.h csapp.h tsh_helper.h


.PHONY: all
all: $(FILES)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

# Compile tsh with link-time interpositioning
tsh: LDFLAGS += $(WRAPCFLAGS)
tsh: tsh.o wrapper.o csapp.o tsh_helper.o

sdriver: sdriver.o
runtrace: runtrace.o csapp.o


# Clean up
.PHONY: clean
clean:
	rm -f *.o *~ $(FILES)
	rm -rf runtrace.tmp

# Create Hand-in
.PHONY: handin
handin: $(HANDIN_TAR)

$(HANDIN_TAR): $(HANDIN_FILES)
	tar cvf $@ $^

# Submit to Autolab
.PHONY: submit
submit: $(HANDIN_TAR)
	@echo "I affirm that I have complied with this course's academic integrity policy as"
	@echo -n "defined at https://www.cs.cmu.edu/~213/academicintegrity.html [y/N]: "
	@read -n 1 && echo && echo $$REPLY | grep -iq "^y"
	@autolab submit $(COURSECODE):$(LAB) $<


# Rule to format tsh.c
.PHONY: format
format: tsh.c
	$(LLVM_PATH)clang-format -style=file -i $^


# Rule to ensure that tsh.c is formatted properly
.PHONY: check-format
check-format: tsh.c
	@$(LLVM_PATH)clang-format -style=file $< | cmp --silent $< - || ( \
	  echo; \
	  echo "ERROR: The formatting of $< is inconsistent with clang-format."; \
	  echo "       For details, see https://cs.cmu.edu/~213/codeStyle.html"; \
	  echo "       To reformat your code, run \"make format\"."; \
	  echo; \
	  exit 1)

# Add check-format dependencies
ifneq ($(NOFORMAT),1)
tsh.o: check-format
submit: check-format
endif
