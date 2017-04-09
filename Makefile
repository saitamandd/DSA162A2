all: dsa162a2

a01: dbLib.o eventLib.o main.o processData.o
	g++ main.o dbLib.o eventLib.o processData.o -std=c++11 -o dsa162a2

main.o: main.cpp dsaLib.h
	g++ -c main.cpp -std=c++11
eventLib.o: eventLib.cpp dsaLib.h
	g++ -c eventLib.cpp -std=c++11
dbLib.o: dbLib.cpp dsaLib.h eventLib.h
	g++ -c dbLib.cpp -std=c++11
processData.o: processData.cpp dsaLib.h eventLib.h dbLib.h
    g++ -c processData.cpp -std=c++11

clean:
	rm *.o dsa162a2
