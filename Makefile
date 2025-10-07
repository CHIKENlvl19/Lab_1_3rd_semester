CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/myArray.cpp \
       $(SRC_DIR)/myStack.cpp \
       $(SRC_DIR)/myQueue.cpp \
       $(SRC_DIR)/mySinglyLinkedList.cpp \
       $(SRC_DIR)/myDoublyLinkedList.cpp \
       $(SRC_DIR)/myAVLTree.cpp \
       main.cpp

OBJS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))

TARGET = dbms

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
