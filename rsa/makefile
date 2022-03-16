CC=gcc
CFLAGS=-I. -lm
FILES=rsa.o encrypt.o decrypt.o utils.o
EXE=rsa

run: $(EXE)
	@echo "Run $(EXE) file"
	@./$(EXE)

compile: $(FILES)
	@$(CC) -o $(EXE) $(FILES) $(CFLAGS)
	@rm $(FILES)
	@chmod +x $(EXE)
	@echo "Files $(FILES) compiled"

$(EXE): compile

clean: 
	@touch $(EXE) $(FILES)
	@rm $(EXE) $(FILES)