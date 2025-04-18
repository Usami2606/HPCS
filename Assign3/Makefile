BIN_DIR = bin
TARGET = $(BIN_DIR)/runprog
FILE ?= p2p.c
TIMER = Timer.c

run:
	mkdir -p $(BIN_DIR)
	mpicc -std=c99 -o $(TARGET) $(FILE) $(TIMER)

clean:
	rm -rf $(BIN_DIR)
