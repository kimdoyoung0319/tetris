tetris: main.o board.o block.o
	g++ -o tetris main.o board.o block.o
    
main.o: main.cpp board.h block.h
	g++ -c main.cpp
    
board.o: board.cpp board.h block.h
	g++ -c board.cpp

block.o: block.cpp block.h
	g++ -c block.cpp
    
clean:
	rm -f tetris main.o board.o block.o