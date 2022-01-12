CC = c++

CXXFLAGS = -Wall -std=c++17
CXXFLAGS += -Iinclude/
LDFLAGS = -framework OpenCL

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = mayCL
BIN = lib

.PHONY: all clean

all: dirs libs $(PROGRAM)

dirs:
	mkdir -p ./$(BIN)
	mkdir -p ./$(BIN)/static

libs:

$(PROGRAM): $(OBJ)
	ar rcs $(BIN)/static/lib$(PROGRAM).a $^

%.o: %.cpp
	$(CC) -o $@ -c $< $(CXXFLAGS) 

clean:
	rm -rf $(BIN)/static $(OBJ)