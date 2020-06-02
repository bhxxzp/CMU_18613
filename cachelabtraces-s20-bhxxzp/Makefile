all: handin

handin:
	tar cvf handin.tar traces/*

submit: handin
	@read -n 1 -p "I affirm that I have complied with this course's academic integrity policy as defined at https://www.cs.cmu.edu/~213/academicintegrity.html [y/N]: " && echo && echo $$REPLY | grep -iq "^y"
	@autolab submit 15213-s20:cachelabtraces handin.tar -f

