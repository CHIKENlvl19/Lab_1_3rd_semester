CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = dbms

OBJDIR = obj
INCLUDES = -Iinclude

SOURCES = src/myArray.cpp src/myStack.cpp src/myQueue.cpp src/mySinglyLinkedList.cpp main.cpp
OBJECTS = $(OBJDIR)/myArray.o $(OBJDIR)/myStack.o $(OBJDIR)/myQueue.o $(OBJDIR)/mySinglyLinkedList.o $(OBJDIR)/main.o

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean