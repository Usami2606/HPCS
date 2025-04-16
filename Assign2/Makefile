# Makefile

BIN_DIR = bin
TARGET = $(BIN_DIR)/ompsum
SRC = ompsum.c

$(TARGET): $(SRC)
	mkdir -p $(BIN_DIR)
	gcc -fopenmp -o $(TARGET) $(SRC)

clean:
	rm -rf $(BIN_DIR)
