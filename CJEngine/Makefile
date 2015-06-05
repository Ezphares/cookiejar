CC=g++
CCFLAGS=-g -Wall -Werror -std=c++11 -I. -c
#TODO: -lmingw32 if problems arise
LDSTD=-lgcc
LDIMAGE=-lpng -lz
LDOGL=-lglew32 -lglfw3dll -lopengl32
LDFLAGS=$(LDSTD) $(LDIMAGE) $(LDOGL)
RM=del

SRC=main.cpp \
componentmodel\\entitymanager.cpp componentmodel\\componentmanager.cpp componentmodel\\entityinterface.cpp



OBJ=$(SRC:.cpp=.o)
EXE=CJEngine.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

rebuild: clean

clean:
	$(RM) $(OBJ) $(EXE)

