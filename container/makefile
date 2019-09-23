CC = gcc
CFLAGS = -Wall -ansi -pedantic -I.
DEPS = ds_memory.h
OBJ = ds_memory.o TestMain.o
EXE = TestMain

all: $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: all
	./$(EXE)

clean:
	rm %.o $(EXE) "test.bin"
