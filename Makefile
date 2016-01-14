CXX = g++
.DEFAULT_GOAL := tictactoe

Game: Game.cpp
	$(CXX) -c Game.cpp -o Game.o

Player: Player.cpp
	$(CXX) -c Player.cpp -o Player.o

test: test.cpp
	$(CXX) -c test.cpp -o test.o

main: main.cpp
	$(CXX) -c main.cpp -o main.o

debug: Game.o Player.o test.o 
	$(CXX) -g -lm Game.o Player.o test.o -o debug 

tictactoe: Game.o Player.o main.o
	$(CXX) -lm Game.o Player.o main.o -o tictactoe

clean: 
	rm -f *.o tictactoe debug 
