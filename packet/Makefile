CC := gcc

FILE = fxcn_cksum.o
BIN=fxcn_cksum

.PHONY: clean

$(BIN):$(FILE)
	gcc -o $@ $^

clean:
	rm -f *.o  $(BIN)
