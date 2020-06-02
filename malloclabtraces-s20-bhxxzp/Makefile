SHELL = /bin/bash

TRACEFILES =
TRACEFILES += traces/tr1.rep
TRACEFILES += traces/tr2.rep
TRACEFILES += traces/tr3.rep

.PHONY: all
all: handin.tar

.PHONY: handin
handin: handin.tar

handin.tar: $(TRACEFILES)
	tar cvf $@ $^

.PHONY: submit
submit: handin
	@read -n 1 -p "I affirm that I have complied with this course's academic integrity policy as defined at https://www.cs.cmu.edu/~213/academicintegrity.html [y/N]: " && echo && echo $$REPLY | grep -iq "^y"
	@autolab submit 15213-s20:malloclabtraces handin.tar -f

.PHONY: clean
clean:
	rm -rf .tracelog.txt handin.tar
