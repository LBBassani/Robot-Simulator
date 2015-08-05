all:
	g++ -c *.cpp -std=c++11
	g++ -o wcg *.o -lglut -lGL -lX11 -lGLU -lm -std=c++11

clean:
	rm *.o
	rm wcg
