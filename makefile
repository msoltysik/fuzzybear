all:
	flex -o scanner.cpp src/scanner.l
	bison -o parser.cpp -d src/parser.y
	g++ -g parser.cpp scanner.cpp

clean:
	rm -rf parser.cpp scanner.cpp