# Automatically find the first .cpp file in the directory
SRC = $(wildcard *.cpp)
TARGET = $(basename $(SRC))

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -fsanitize=address

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $mmain
	@echo "Compiled successfully! Run with: ./$mmain"

clean:
	rm -f $(TARGET)
