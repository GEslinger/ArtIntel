CXX = g++
STD = -std=c++11
EXECS = iris
OBJS = DataTable.o tools.o
CXXFLAGS = $(STD)
LFLAGS = $(STD)

all : $(EXECS)

iris : $(OBJS) iris.cpp
	$(CXX) $(OBJS) -o iris $(LFLAGS) iris.cpp

clean :
	rm -f ./*.png $(OBJS)
	rm -rf *~