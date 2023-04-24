movieDB: main.o
	g++ -o movieDB main.o
 
main.o: main.cpp collection.cpp
	g++ -c main.cpp collection.cpp

clean:
		rm -f *.o