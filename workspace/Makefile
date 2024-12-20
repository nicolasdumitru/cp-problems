CXX=clang++

all: build

main: main.cpp
	$(CXX) -o $@ \
		-std=c++17 \
		-Wall \
		-Werror \
		-Wpedantic \
		-pedantic \
		-O2 \
		#-fsanitize=address \
		#-fsanitize=undefined \
		$^

build: main

run: main
	./$^

debug: main.cpp
	g++ -o main -Wall -Wpedantic -ggdb2 $^

clean:
	rm main
