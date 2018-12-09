CC = g++
CFLAGS = -std=c++14
TARGET = HidatoPuzzle
SOURCES = main.cpp \
          Point.cpp \
          Element.cpp \
					HidatoGenerator.cpp \
					GeneratorManager.cpp \
					HidatoSolver.cpp \
					SolverManager.cpp \

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -rf *.o $(TARGET)
