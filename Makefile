movieDB: main.o
	g++ -o movieDB console.o database.o

main.o: console.cpp database.cpp
	g++ -c console.cpp database.cpp

filter.o: filter.cpp
	g++ -c filter.cpp

clean:
	rm -f *.o