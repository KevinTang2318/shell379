CC = g++
CFLAGS = -Wall
CLIBS = -lstdc++
INC = -I src/

all: shell379 sleeper runner

shell379: main.o shell_runner.o process.o process_table.o command_func.o
	${CC} ${CFLAGS} -o shell379 main.o shell_runner.o process.o process_table.o command_func.o ${CLIBS}

main.o: main.cpp
	${CC} ${CFLAGS} ${INC} -c main.cpp

shell_runner.o: src/shell_runner.cpp src/shell_runner.h
	${CC} ${CFLAGS} ${INC} -c src/shell_runner.cpp src/shell_runner.h

process.o: src/process.h src/process.cpp
	${CC} ${CFLAGS} ${INC} -c src/process.h src/process.cpp

process_table.o: src/process_table.h src/process_table.cpp
	${CC} ${CFLAGS} ${INC} -c src/process_table.h src/process_table.cpp

command_func.o: src/command_func.h src/command_func.cpp
	${CC} ${CFLAGS} ${INC} -c src/command_func.h src/command_func.cpp


sleeper: src/sleeper.cpp
	${CC} ${CFLAGS} -o sleeper src/sleeper.cpp

runner: src/runner.cpp
	${CC} -o runner src/runner.cpp

clean:
	rm -rf *.o
	rm -rf src/*.gch
	rm sleeper runner shell379
