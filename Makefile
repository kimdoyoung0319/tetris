tetris: main.o board.o block.o screen.o game.o
	g++ -o tetris main.o board.o block.o screen.o game.o -lncursesw

test: test.cpp
	g++ test.cpp -o test -lncursesw
    
main.o: main.cpp board.h block.h
	g++ -c -g main.cpp
    
board.o: board.cpp board.h block.h
	g++ -c -g board.cpp

block.o: block.cpp block.h
	g++ -c -g block.cpp
    
screen.o: screen.cpp screen.h
	g++ -c -g screen.cpp -lncursesw

game.o: game.cpp game.h
	g++ -c -g game.cpp

clean:
	rm -f tetris test main.o board.o block.o screen.o game.o
