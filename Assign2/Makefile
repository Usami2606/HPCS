BIN_DIR = bin

TARGETS = $(BIN_DIR)/ompsum $(BIN_DIR)/sumprog $(BIN_DIR)/hello

$(BIN_DIR)/ompsum: ompsum.c sum.c
	mkdir -p $(BIN_DIR)
	gcc -fopenmp -o $@ ompsum.c sum.c

$(BIN_DIR)/sumprog: sum.c
	mkdir -p $(BIN_DIR)
	gcc -o $@ sum.c

$(BIN_DIR)/hello: hello.c
	mkdir -p $(BIN_DIR)
	gcc -o $@ hello.c

clean:
	rm -rf $(BIN_DIR)
