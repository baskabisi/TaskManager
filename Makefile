all:
	g++ -pthread -std=c++17 -o main main.cpp TaskManager.cpp EvenCounter.cpp OddCounter.cpp
	./main

