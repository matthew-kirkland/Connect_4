ifeq ($(OS), Windows_NT)
    RM = del /F /Q
    RMDIR = rmdir /S /Q
    TARGET = game.exe
else
    OS := $(shell uname)
    ifeq ($(OS), Linux)
        RM = rm -f
        RMDIR = rm -rf
        TARGET = game
    else ifeq ($(OS), Darwin)
        RM = rm -f
        RMDIR = rm -rf
        TARGET = game
    endif
endif

# Use g++ for C++ code
CXX = g++

CXXFLAGS = -Wall -Wextra
INCLUDES = -Iinclude

# List your .cpp source files here
SRC = game.cpp engine/evaluate.cpp engine/minimax.cpp

OBJ = $(SRC:.cpp=.o)

DEPS = include/game.h include/evaluate.h include/minimax.h

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o
	$(RMDIR) engine
	$(RM) $(TARGET)