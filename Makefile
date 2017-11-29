CC = g++
CFLAGS = -c -Wall
LDFLAGS = 
SOURCES = main.cpp Graph.cpp MaxHeap.cpp maxHeapDijkstra.cpp noHeapDijkstra.cpp Kruskal.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
