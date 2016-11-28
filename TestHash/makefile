OBJS = testHash.o myHash.o
SOURCE = testHash.cpp myHash.cpp 
HEADER = defines.h myHash.h 
 OUT = test_hash
  CC = g++
FLAGS = -c -g
DELETE = $(OBJS) $(OUT)
DEPENDENCIES =

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)


$(OBJS): $(SOURCE) $(HEADER)
	$(CC) $(FLAGS) $(SOURCE)

deb:
	gdb $(OUT)

val:
	valgrind --leak-check=yes ./$(OUT)

clean:
	rm -f $(DELETE)

run:
	clear
	./$(OUT)

#always take ex3 from syspro as reference
#mingw32-make.exe for windows through git bash

