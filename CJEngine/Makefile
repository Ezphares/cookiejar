CC=g++
CCFLAGS=-g -Wall -std=c++11 -I. -DUSE_GL_RENDERER -mwindows -c
#TODO: -lmingw32 if problems arise
LDSTD=-lgcc
LDIMAGE=-lpng -lz
LDOGL=-lglew32 -lglfw3dll -lopengl32
LDFLAGS=$(LDSTD) $(LDIMAGE) $(LDOGL)
RM=del

SRC=main.cpp \
componentmodel\\entitymanager.cpp componentmodel\\componentmanager.cpp componentmodel\\entityinterface.cpp \
physics\\physicsmanager.cpp \
io\\filereader.cpp \
window\\glwindow.cpp \
window\\input\\glinputcontroller.cpp \
window\\graphics\\glbuffer.cpp window\\graphics\\glgraphicscontroller.cpp window\\graphics\\glshaderprogram.cpp window\\graphics\\gltexture.cpp window\\graphics\\glvertexarray.cpp window\\graphics\\sprite.cpp


OBJ=$(SRC:.cpp=.o)
EXE=CJEngine.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

rebuild: clean

clean:
	$(RM) $(OBJ) $(EXE)

