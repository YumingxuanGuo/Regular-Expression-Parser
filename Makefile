CXX=clang++
CXX_FLAGS=-std=c++20 -g -Wall -fstandalone-debug -O0 -Wextra -Werror

default: main.cpp src/Regex.cpp
	${CXX} ${CXX_FLAGS} -o main main.cpp src/Regex.cpp

clean:
	rm -f main *.o *~