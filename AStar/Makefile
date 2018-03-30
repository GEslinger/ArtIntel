CXX = g++
STD = -std=c++11
EXECS = Runner
OBJS = Node.o AStar.o Runner.o
CXXFLAGS = $(STD)
LFLAGS = $(STD) $(LIBS)

all : $(EXECS)

Runner : $(OBJS) 
	$(CXX) $(OBJS) -o Runner $(LFLAGS)

clean :
	rm -f ./*.png $(EXECS) $(OBJS)
	rm -rf *~