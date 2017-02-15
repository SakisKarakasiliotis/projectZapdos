OBJS = bfs.o buffer.o index.o list_node.o main.o myHash.o Q.o updateIndex.o grail.o component.o stronglyConnectedComponents.o stack.o rank.o tarjan.o StaticBFS.o job.o dynamicGraph.o staticGraph.o scheduler.o jobQueue.o staticJob.o dynamicJob.o
SOURCE = bfs.cpp buffer.cpp index.cpp list_node.cpp main.cpp myHash.cpp Q.cpp updateIndex.cpp grail.cpp component.cpp stronglyConnectedComponents.cpp stack.cpp rank.cpp tarjan.cpp StaticBFS.cpp job.cpp dynamicGraph.cpp staticGraph.cpp scheduler.cpp jobQueue.cpp staticJob.cpp dynamicJob.cpp
HEADER = bfs.h buffer.h component.h defines.h dynamicGraph.h grail.h index.h job.h jobQueue.h list_node.h myHash.h Q.h rank.h scheduler.h stack.h StaticBFS.h staticGraph.h stronglyConnectedComponents.h updateIndex.h

 OUT = zapdos
  CC = g++
FLAGS = -c -g
DELETE = $(OBJS) $(OUT)
DEPENDENCIES = -lpthread

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(DEPENDENCIES)


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



