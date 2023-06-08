CXX = g++
CXXFLAGS = -g -std=c++11 -I../
LDFLAGS = $(shell pkg-config --libs json)

SOURCES = console.cpp filter.cpp database.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = movieDB

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
