CXX=		g++
CXXFLAGS=	-std=c++11 -g

all: comatose

comatose: board.o bomb.o BOSS.o creature.o human.o insides.o lvlchange.o pickup.o setlvl.o symbol.o
	$(CXX) $^ -static -static-libgcc -static-libstdc++ -o $@
