CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Default target
all: lab11

# Link step
lab11: main.o Matrix.o
	$(CXX) $(CXXFLAGS) -o lab11 main.o Matrix.o

# Compile main.cpp into main.o
main.o: main.cpp Matrix.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compile Matrix.cpp into Matrix.o
Matrix.o: Matrix.cpp Matrix.h
	$(CXX) $(CXXFLAGS) -c Matrix.cpp

# Remove build files
clean:
	rm -f *.o lab11
