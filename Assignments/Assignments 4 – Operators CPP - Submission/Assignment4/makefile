Ass4: Game.o main.o Map.o Robot.o
	g++ *.cpp -o Ass4
Game.o: Game.cpp Map.h Robot.h Game.h
	g++ -c Game.cpp
main.o: main.cpp Game.h Robot.h Map.h
	g++ -c main.cpp
Map.o: Map.cpp Map.h
	g++ -c Map.cpp
Robot.o: Robot.cpp Robot.h
	g++ -c Robot.cpp
clean:
	rm -f *.o Ass4

