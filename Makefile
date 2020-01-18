CC=g++
CFLAGS  = -Wall -std=c++17 -pthread -fopenmp
LFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -fopenmp

SOURCES += main.cpp
SOURCES += Application.cpp
SOURCES += RandomPointGenerator.cpp
SOURCES += Renderer.cpp
SOURCES += JarvisSheath.cpp
SOURCES += SheathGrahamScan.cpp

# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

all: clean compile run

re-compile: $(OBJS)
	$(CC) $(OBJS) -o app.out $(LFLAGS)

compile: clean re-compile

run : 
	./app.out 

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o *.out