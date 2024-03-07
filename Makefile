CC = g++
DEPS = particle.h shader.h simulator.h
OBJ = particle.o shader.o simulator.o
CFLAGS = -lGL -lglfw -lGLEW -ldl
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

make: main.cpp particle.o shader.o simulator.o
	$(CC) -o bin/IdealGasSimulator $^ $(CFLAGS)

clean:
	rm -f *.o bin/*
