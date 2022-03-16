CC=gcc
CFLAGS=-I. -lm
FILES=des.o key64to48.o encrypt.o decrypt.o cipher.o permutation.o
EXE=des
INPUT_FILE=inputs/input.txt
RESULT_FILE=outputs/result.txt
TMP_FILES=decrypted.txt outputs/cipher.txt bits.txt
TMPS_DIR=tmps outputs



run: $(EXE)
	@echo "Run $(EXE) file"
	@./$(EXE)

compile: $(FILES)
	@$(CC) -o $(EXE) $(FILES) $(CFLAGS)
	@rm $(FILES)
	@chmod +x $(EXE)
	@echo "Files $(FILES) compiled"

$(EXE): compile
	
diff: 
	@touch $(RESULT_FILE) $(INPUT_FILE)
	@echo "There is a `diff $(RESULT_FILE) $(INPUT_FILE) | wc -l` differents rows between result.txt and input.txt"

clean: 
	@touch $(EXE) $(FILES)
	@rm $(EXE) $(FILES)
	@mkdir -p $(TMPS_DIR)
	@rm -r $(TMPS_DIR)