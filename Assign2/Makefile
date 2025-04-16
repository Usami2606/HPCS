BIN_DIR = bin
TARGET = $(BIN_DIR)/ompsum
SRC = ompsum.c sum.c hello.c

$(TARGET): $(SRC)
	mkdir -p $(BIN_DIR)
	gcc -fopenmp -o $(TARGET) $(SRC)

clean:
	rm -rf $(BIN_DIR)
