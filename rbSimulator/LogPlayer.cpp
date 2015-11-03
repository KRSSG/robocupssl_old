#include <string>
#include "config.h"
#include "logplayer.h"

logplayer::logplayer(char *name)
{
  ins = fopen(name, "w");
  reader = true;
  stime = new QTime();
  stime->start();
}

logplayer::~logplayer(void)
{
    close();
}

void logplayer::open(const char* name , char* mode)
{
  close();
  ins = fopen(name,"w");
}

void logplayer::close()
{
  if(ins)
    fclose(ins);
}
bool logplayer::readBall(float *ballx,float *bally)
{
    int time;
  if(fscanf(ins,"%d%f%f",&time,ballx,bally)==EOF)
  {
    ballx=0;
    bally=0;
    return false;
  }
  return true;
}
bool logplayer::readBot(float *botx,float *boty,float *orient)
{
  if(fscanf(ins,"%f%f%f",botx,boty,orient)==EOF)
  {
    botx=0;
    boty=0;
    orient=0;
    return false;
  }
  return true;
}
void logplayer::writeBall(float ballx,float bally)
{
  fprintf(ins,"\n%d\t%f\t%f\t",stime->elapsed(),ballx,bally);
}
void logplayer::writeBot(float botx,float boty,float orient)
{
  fprintf(ins,"%f\t%f\t%f\t",botx,boty,orient);
}
//TODO: record also the Canvas object graphic logs