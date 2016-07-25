CC=g++ -I/opt/X11/include
LIBS= -lGL -lglut

all:
	$(CC) -L/opt/X11/lib/ *.cpp $(LIBS) -o RayTracer

run: all
	./RayTracer

clean: 
	rm -f RayTracer *.o
