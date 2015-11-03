#include <fstream>
#include <QTime>
class logplayer
{
public:
  logplayer(char *name="temp.log");
  ~logplayer(void);
  void open(const char* name="temp.log",char *mode="w");
  void close();
  bool readBall(float *ballx,float *bally);
  bool readBot(float *botx,float *boty,float *orient);
  void writeBall(float ballx,float bally);
  void writeBot(float botx,float boty,float orient);

private:
  FILE *ins;
  int reader;
  QTime *stime;
};
