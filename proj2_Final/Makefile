all: huftree

# huftree depends on 2 object files (priorityqueue.o, codetree.o)
huftree :  huftree.cc priorityqueue.o codetree.o
	g++ -Wall -g huftree.cc priorityqueue.o codetree.o -o huftree

# codetree depends on codetree.cc, codetree.h, and priorityqueue.h
codetree.o: codetree.cc codetree.h priorityqueue.h
	g++ -Wall -c -g codetree.cc -o codetree.o

# priorityqueue depends on priorityqueue.cc, priorityqueue.h, and codetree.h
priorityqueue.o: priorityqueue.cc priorityqueue.h codetree.h
	g++ -Wall -c -g priorityqueue.cc -o priorityqueue.o

# "clean" to remove other files except original source codes
clean:
	rm *.o
	rm huftree
