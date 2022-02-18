CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = card.o joker.o player.o head.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = hydra

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
