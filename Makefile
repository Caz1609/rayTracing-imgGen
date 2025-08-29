run: exe
	./exe
	loupe 1.png
	
exe: funcs.o main.o funcs.h
	g++ main.o funcs.o -o exe

main.o: main.cpp
	g++ -c main.cpp -o main.o

funcs.o: funcs.cpp
	g++ -c funcs.cpp -o funcs.o

clean:
	rm -f *.o exe
