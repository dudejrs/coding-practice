CC = g++
FLAGS=-std=c++14
BOOST_FLAGS=-L /Users/kimdeokyoung/boost_1_81_0/stage/lib

PATH := $(PATH):/Users/kimdeokyoung/boost_1_81_0

CPP_SOURCES := $(wildcard *.cpp)
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)
CPP_EXECUTABLE := $(CPP_SOURCES:.cpp=.out)


all : $(CPP_EXECUTABLE)

$(CPP_EXECUTABLE):$(CPP_SOURCES)
	$(CC) $(@:.out=.cpp) $(FLAGS) -I /Users/kimdeokyoung/boost_1_81_0  -o $@


clean : 
	rm -f *.o
	rm -f $(CPP_EXECUTABLE)