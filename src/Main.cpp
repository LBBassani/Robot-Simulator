#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "WindowCallBacks.h"
#include "GLDraw.h"
#include <GL/glut.h>
#include "Constants.h"
#include "World.h"
#include <cmath>
#include <string.h>
#include "VsssUFES.h"

#include <jsoncpp/json/json.h>
#include <sys/socket.h>
#include <sstream>

#include "ServerSocket.h"
#include "SocketException.h"

using namespace std;
/*------------------------------------------------------------------------------------------------*/

void test(int, char **);

void server(int, char **);

void echoserver(int, char **);

void error(const char *msg)
{
    perror(msg);
    exit(1);
};


int main( int argc, char ** argv ){

    if (argc > 1){
        if(!strcmp(argv[1], "--test")) test(argc, argv);
        if(!strcmp(argv[1], "--echo-server")) echoserver(argc, argv);
        if(!strcmp(argv[1], "--start-server")) server(argc, argv);
    }
    return 0;
}

void server(int argc, char ** argv){
  std::cout << "running....\n";
  int port = 40003;
  if (argc > 2) port = (atoi(argv[2]));

  try{
    ServerSocket server(port);
    // Create the socket

    while ( true ){

      ServerSocket new_sock;
      server.accept ( new_sock );

      try{
          while ( true ){
            // Recebe dados pela porta
            std::string header, data;
            new_sock >> header;
            // Quebra o header para ter as informações
            std::vector<std::string> headerwords;
            std::istringstream iss (header) ;
            for(std::string s; iss >> s; )
              headerwords.push_back(s);

            // Se o método for post ou put, recebe corpo
            if (!headerwords[0].compare("POST") || !headerwords[0].compare("PUT"))
              new_sock >> data;
              Json::Reader reader;
              Json::Value obj;
              reader.parse(data, obj);
              std::cout << headerwords[0] << endl << data << endl;
              
              // monta a resposta
              Json::Value resp;
              Json::FastWriter fastWriter;
              resp["result"] = obj["method"];
              resp["id"] = obj["id"];
              std::string response = fastWriter.write(resp);
              std::vector<std::string> responsehearder;

              responsehearder.push_back("HTTP/1.1");
              responsehearder.push_back("200");
              responsehearder.push_back("OK\n");
              responsehearder.push_back("Content-Type: application/json\n");
              responsehearder.push_back("Content-Length:");

            // Responde a requisição
            /* Json::Value resp;
            resp["result"] = obj["method"];
            ;
            std::string response = fastWriter.write(resp);
            new_sock << response; */
          }
        }
      catch ( SocketException& ) {}

	  } 
  } catch ( SocketException& e ){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

}

void echoserver(int argc, char ** argv){
  std::cout << "running....\n";
  int port = 30000;
  if (argc > 2) port = (atoi(argv[2]));

  try{
    ServerSocket server(port);
    // Create the socket

    while ( true ){

      ServerSocket new_sock;
      server.accept ( new_sock );

      try{
          while ( true ){
            std::string data;
            new_sock >> data;
            new_sock << data;
          }
        }
      catch ( SocketException& ) {}

	  } 
  } catch ( SocketException& e ){
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

}

void test( int argc, char ** argv){
    VsssUFES g("Test User");
    g.greet();

    const double width = 720;
    const double height = 720;
    const int simulationMaxSteps = 60*15;
    int stepCounter = 0;
    window *w = new window(width, height);
    glutInit( &argc, argv );
    initGl();


    World world;
    int robotId = 0;

    for(float theta = 0; theta < 2*M_PI; theta += (2*M_PI/10))
    {
        for(float r = 0; r < 1.2/2; r += ((1.2/2)/4))
        {
            Robot * robot = new Robot(robotId++, ROBOTLEN, r*cos(theta), r*sin(theta), -M_PI/2);
            world.insertRobot(robot);
        }
    }

    double lastTime = getCurrentTime();
    double currentTime = lastTime;

    while(true)
	{
        currentTime = getCurrentTime();
		if( !w->process( mouseFunc, keyPress, keyRelease ) ) break;

		if( ( currentTime - lastTime ) >= TIME_STEP )
		{
            if(stepCounter++ >= simulationMaxSteps) break;
            w->update();
			lastTime += TIME_STEP;
            world.evolve(TIME_STEP);
            drawAll(world);
		}
	}
}
