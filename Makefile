movieDB: main.o
	g++ -g -o movieDB console.o filter.o database.o 

main.o: console.cpp filter.cpp database.cpp 
	g++ -c console.cpp filter.cpp database.cpp 

clean:
	rm -f *.o $(objects) movieDB