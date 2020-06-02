#
# Student makefile for Cache Lab
#
CC = gcc
CFLAGS = -g -Wall -Werror -std=c99
LLVM_PATH = /usr/local/depot/llvm-7.0/bin/

all: csim test-trans tracegen-ct

.PHONY: submit

submit: handin
		@read -n 1 -p "I affirm that I have complied with this course's academic integrity policy as defined at https://www.cs.cmu.edu/~213/academicintegrity.html [y/N]: " && echo && echo $$REPLY | grep -iq "^y"
		@autolab submit 15213-s20:cachelab handin.tar -f

handin: format csim test-trans
	-tar -cvf handin.tar  csim.c trans.c

format: csim.c trans.c
	clang-format -style=file -i csim.c trans.c

csim: csim.c cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o csim csim.c cachelab.c -lm

test-trans: test-trans.c trans.o cachelab.c cachelab.h
	$(CC) $(CFLAGS) -o test-trans test-trans.c cachelab.c trans.o

tracegen-ct: tracegen-ct.c trans.c cachelab.c
	$(LLVM_PATH)clang -emit-llvm -S -O0 trans.c -o trans.bc
	$(LLVM_PATH)opt trans.bc -load=ct/Check.so -Check -o trans.bc
	$(LLVM_PATH)clang trans.c -O3 -emit-llvm -S -o trans.bc
	$(LLVM_PATH)opt trans.bc -load=ct/CLabInst.so -CLabInst -o trans_ct.bc
	$(LLVM_PATH)llvm-link trans_ct.bc ct/ct.bc -o trans_fin.bc
	$(LLVM_PATH)clang -o tracegen-ct -O3 trans_fin.bc cachelab.c tracegen-ct.c -pthread -lrt

trans.o: CFLAGS += -Wno-unused-const-variable -Wno-unused-function \
	-Wno-unused-parameter
trans.o: trans.c
	$(CC) $(CFLAGS) -O0 -c trans.c

#
# Clean the src dirctory
#
clean:
	rm -rf *.o
	rm -f *.bc
	rm -f csim
	rm -f test-trans tracegen tracegen-ct
	rm -f trace.all trace.f*
	rm -f .csim_results .marker
