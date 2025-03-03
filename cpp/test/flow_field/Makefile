CXX = g++
CXXFLAGS = -Wall
TARGET = test_flow_field
SRCS = test.cpp ../../src/mesh2d.cpp ../../src/flow_field.cpp
INCDIR = -I../../inc
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)