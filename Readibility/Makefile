CXX = g++
STD = -std=c++11
EXECS = Analyze
OBJS = Analyze.o
CXXFLAGS = $(STD)
LFLAGS = $(STD) $(LIBS)

all : $(EXECS)

Analyze : $(OBJS) 
	$(CXX) $(OBJS) -o Analyze $(LFLAGS)

clean :
	rm -f ./*.png $(EXECS) $(OBJS)
	rm -rf *~