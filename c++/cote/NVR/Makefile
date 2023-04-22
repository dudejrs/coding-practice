CC= g++
FLAGS=-std=c++14
CPP_SOURCES :=$(wildcard *.cpp)
CPP_OBJECTS :=$(CPP_SOURCES:.cpp=.o)
CPP_TARGET :=$(CPP_SOURCES:.cpp=)
CPP_EXECUTABLE :=$(CPP_SOURCES:.cpp=.out)

all : $(CPP_TARGET) 

$(CPP_TARGET):$(CPP_SOURCES)
	$(CC) $@.cpp $(FLAGS) -o $@.out

clean : 
	rm -f *.o
	rm -f $(CPP_EXECUTABLE)

