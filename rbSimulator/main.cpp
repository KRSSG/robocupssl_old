#include <cstdio>
#include "config.h"
#include "physxEngineMain.h"
#include "RbSimulator.h"
#include <QtGui/QApplication>
#include "RbCentral.h"
#include "rbCommDef.h"

using namespace Simulator;
using namespace HAL;
using namespace PhysxEngine;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  PosInfo         *posInfo = new PosInfo();
  PhysxEngineMain *engine  = new PhysxEngineMain(posInfo);
  
  RbCentral       *rbCen   = new RbCentral(posInfo,engine);
  
  RbSimulator     *rbSimu  = new RbSimulator(rbCen);
  
  //--------------------
  rbSimu->show();
  int status = a.exec();

  delete rbSimu;
  rbSimu = NULL;

  delete posInfo;
  posInfo = NULL;

  delete engine;
  engine = NULL;

  delete rbCen;
  rbCen = NULL;

  return status;
}


/*using rbSimulator

Make an object of Simuserver and pass it to rbSimulator

Server *Game=new Server();
rbSimulator *w=new rbSimulator(Game);

or

rbSimulator *w =new rbSimulator(new SimuSerer());
w->show() to show the rbSimulator window

now make a new thread

In main thread just pust a.exec(); where a is the QApplication object created 
at the begining of main

In the new thread Created use w(rbSimulator object) to manage the game state

functions in rbSimulator

1. void setBot(int team, int botNo,float x,float y,float orientation)
Used to give new position to the Bot
team is 0 for yellow and 1 for blue as defined in config.h

2. void setBall(float x,float y)
Used to give new position to the Ball
Configurations of drawing the Bot and Ball (radius etc.) aare defined in conig.h file

3. GCanvas* addCanvas(int r,int g,int b)
Used to add a new cnvas to the field.
This canvas can be used to draw graphical Items

Now using the GCanvas objects
int addCircle(int x,int y,int radius);
int addLine(int x1,int y1,int x2,int y2);
int contLineTo(int x,int y);
int addEllipse(int centerX,int centerY,int a,int b);
int addText(char* str);
int contCubicTo(int x1,int y1,int x2,int y2,int x3,int y3);
int contQuadTo(int x1,int y1,int x2,int y2);
bool removeItem(int itemNo=0);
void clear();

The functions return the Id of the item No which can be used to remove the Item
Max no of items added per canvas=200;
MAX no of Text added is 50
these can be changed from the config.h file

*/
