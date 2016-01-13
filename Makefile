CXX = g++

Game: Game.cpp
	$(CXX) -c Game.cpp -o Game.o

Player: Player.cpp
	$(CXX) -c Player.cpp -o Player.o

test: test.cpp
	$(CXX) -c test.cpp -o test.o

debug: Game.o Player.o test.o 
	$(CXX) -g -lm Game.o Player.o test.o -o debug 

clean: 
	rm -f *.o main debug 
