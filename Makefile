CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj

OBJS = $(OBJ_DIR)/myArray.o \
       $(OBJ_DIR)/myStack.o \
       $(OBJ_DIR)/myQueue.o \
       $(OBJ_DIR)/mySinglyLinkedList.o \
       $(OBJ_DIR)/myDoublyLinkedList.o \
       $(OBJ_DIR)/main.o

TARGET = dbms

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# отдельное правило для main.cpp (лежит не в src/)
$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
