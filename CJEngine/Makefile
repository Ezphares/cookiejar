CC=g++
CCFLAGS=-g -Wall -std=c++11 -I.
#TODO: -lmingw32 if problems arise
LDSTD=-lgcc
LDIMAGE=-lpng -lz
LDOGL=-lglew32 -lglfw3dll -lopengl32
LDFLAGS=$(LDSTD) $(LDIMAGE) $(LDOGL)
RM=

SRC=main.cpp
OBJ=$(SRC:.cpp=.o)
EXE=CJEngine.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

rebuild: clean

clean:
	del $(OBJ) $(EXE)
