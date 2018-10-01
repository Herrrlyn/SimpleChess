CXX = g++-5
CXXFLAGS = -Wall -MMD -std=c++14
GRAPHIC = -lX11
OBJECTS = piece.o model.o window.o View.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = chess

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${GRAPHIC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
