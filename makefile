CFLAGS = gcc
CC = -ansi -Wall -pedantic
OBJ = ds_memory.o ds_array.o ds_list.o

all: $(OBJ)

%.o: %.c %.h ds_memory.h
	$(CFLAGS) $(CC) -c $< -o $@
