OBJ := currentsetting.o
BIN := currentsetting
CC = gcc
.PHONY: clean $(BIN)
$(BIN): $(OBJ)
	$(CC) -o $@ $^
clean:
	rm $(BIN) $(OBJ)
