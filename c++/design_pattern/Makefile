CC = g++
FLAGS=-std=c++14



CPP_SOURCES := $(wildcard *.cpp)
CPP_OBJECTS := $(CPP_SOURCES:.cpp=.o)
CPP_EXECUTABLE := $(CPP_SOURCES:.cpp=.out)
CPP_TARGET:= $(CPP_SOURCES:.cpp=)


all : $(CPP_TARGET)

$(CPP_TARGET):$(CPP_SOURCES)
	$(CC) $@.cpp $(FLAGS) -I /Users/kimdeokyoung/boost_1_81_0  -o $@.out


clean : 
	rm -f *.o
	rm -f $(CPP_EXECUTABLE)