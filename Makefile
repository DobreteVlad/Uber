
build:
	g++ --std=c++11 -Wall -Wextra main.cpp -g -o tema2

.PHONY: clean

run:
	./main

clean:
	
	rm tema2
	rm time.out
