
OBJ_DIR = objects
BIN_DIR = bin
SRC_FILES = main.o swap.o 
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES))




main: $(OBJ_FILES) | $(BIN_DIR)
	gcc -o $(BIN_DIR)/$@ $^


$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	gcc -c -o $@ $<


$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@


clean:
	rm -f $(BIN_DIR)/main $(OBJ_DIR)/*.o
	rmdir $(OBJ_DIR) 
	rmdir $(BIN_DIR) 
