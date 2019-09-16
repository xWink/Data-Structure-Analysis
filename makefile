CC = gcc
CFLAGS = -Wall -ansi -g
F1 = ds_memory
F2 = CIS2520_A1_TestMain

all: $(F1).o $(F2).o
	$(CC) $(CFLAGS) -o $(F2) $(F2).o -I $(F1).o

$(F1).o: $(F1).c $(F1).h
	$(CC) $(CFLAGS) -c $(F1).c -o $(F1).o

$(F2): $(F2).c $(F1).c
	$(CC) $(CFLAGS) -c $(F2).c -o $(F2).o

run: all
	./$(F2)

clean:
	rm $(F1).o $(F2).o $(F2) "test.bin"
