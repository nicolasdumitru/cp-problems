CXX=clang++

.PHONY: all
all: build

main: main.cpp
	$(CXX) -o $@ \
		-std=c++17 \
		-Wall \
		-Werror \
		-Wpedantic \
		-pedantic \
		-O2 \
		$^

.PHONY: build
build: main

.PHONY: run
run: main
	./$^

debug: main.cpp
	g++ -o main -Wall -Wpedantic -ggdb2 $^

.PHONY: clean
clean:
	rm main
