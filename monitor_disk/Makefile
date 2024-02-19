BIN := monitor_disk

all: $(BIN)
	echo "build Start"

$(BIN): monitor_disk.c
	gcc -o $@ $^ -lcjson -lcurl

clean:
	rm $(BIN)
