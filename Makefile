CXX = clang++
CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CPPFILES:.cpp=.o)
OUTFILE = render

CXXFLAGS = -std=c++11

.PHONY: clean

all: $(OUTFILE)

clean:
	rm -f $(OBJFILES) $(OUTFILE)

$(OUTFILE): $(OBJFILES)
	$(CXX) -o $@ $^

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

