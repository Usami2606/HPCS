BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= ompsum.c  # デフォルトは ompsum.c

run:
	mkdir -p $(BIN_DIR)
	gcc -fopenmp -o $(TARGET) $(FILE)

clean:
	rm -rf $(BIN_DIR)
