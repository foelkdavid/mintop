CC = zig cc
CFLAGS = -Wall -Wextra -I./include
SRC = src/main.c src/usage.c
BIN_DIR = bin
TARGET = $(BIN_DIR)/mintop

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SRC)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
