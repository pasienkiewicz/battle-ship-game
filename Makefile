build:
	g++ -std=c++17 -O2 -Wall -Wextra -I. -o BattleShipGame $(shell find . -name '*.cpp')