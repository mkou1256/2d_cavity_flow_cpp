CXX = g++
CXXFLAGS = -Wall
TARGET = test_mesh
SRCS = main.cpp ../../mesh2d.cpp
INCDIR = -I../../../inc
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)