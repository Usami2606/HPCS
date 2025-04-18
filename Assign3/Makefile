BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= p2p.c

run:
	mkdir -p $(BIN_DIR)
	mpicc -o $(TARGET) $(FILE)

clean:
	rm -rf $(BIN_DIR)