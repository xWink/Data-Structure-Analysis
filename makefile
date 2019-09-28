CFLAGS = gcc
CC = -ansi -Wall -pedantic
OBJ = main.o ds_memory.o ds_array.o
DEP = ds_memory.h ds_array.h

all: $(OBJ)
	$(CFLAGS) $(OBJ) -o run

%.o: %.c $(DEP)
	$(CFLAGS) $(CC) -c $< -o $@

run: all
	./run

clean: $(OBJ)
	rm $(OBJ) run
