movieDB: console.o
	g++ -o movieDB console.o
 
main.o: console.cpp
	g++ -c console.cpp

clean:
		rm -f *.o