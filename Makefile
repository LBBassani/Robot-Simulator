all:
	g++ -c *.cpp
	g++ -o wcg *.o -lglut -lGL -lX11 -lGLU -lm

clean:
	rm *.o
	rm wcg
