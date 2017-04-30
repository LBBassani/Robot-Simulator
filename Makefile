all:
	clang++ -c *.cpp -std=c++11
	clang++ -o wcg *.o -lglut -lGL -lX11 -lGLU -lm -std=c++11 -g

clean:
	rm *.o
	rm wcg
