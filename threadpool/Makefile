#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

#OBJS =		threadpool.o

LIBS =

#TARGET =	threadpool.exe

SRC=src
OBJPATH=bin/obj
EXAMPLEPATH=bin/example

#$(TARGET):	$(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

#all:	$(TARGET)
#all:
#	g++  $(SRC)/ThreadMutex.cpp -lpthread -c -o $(SRC)/ThreadMutex.o
#	g++  $(SRC)/Task.cpp -lpthread -c -o $(SRC)/Task.o
#	g++  $(SRC)/ThreadPool.cpp -lpthread -c -o $(SRC)/ThreadPool.o
#	g++  $(SRC)/CondVar.o $(SRC)/ThreadMutex.o $(SRC)/Task.o $(SRC)/ThreadPool.o threadpool_test.cpp -lpthread -o threadpool_test

all:
	g++  $(SRC)/ThreadMutex.cpp -lpthread -c -o $(SRC)/ThreadMutex.o
	g++  $(SRC)/Task.cpp -lpthread -c -o $(SRC)/Task.o
	g++  $(SRC)/ThreadPool.cpp -lpthread -c -o $(SRC)/ThreadPool.o
	g++  $(SRC)/ThreadMutex.o $(SRC)/Task.o $(SRC)/ThreadPool.o $(SRC)/threadpooltest.cpp -lpthread -o threadpool_test

#clean:
#	rm -f $(OBJS) $(TARGET)
