OBJS = buffer.o list_node.o index.o main.o
SOURCE = buffer.cpp list_node.cpp index.cpp main.cpp
HEADER = buffer.h list_node.h index.h defines.h
 OUT = zapdos
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

