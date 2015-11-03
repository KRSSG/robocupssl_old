#ifndef INCL_SERVER_H
#define INCL_SERVER_H

#include <cstdio>
#include <netraw.h>
#include <cstring>
#include <QTime>
#include <Qmutex>
#include "config.h"
#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "messages_robocup_ssl_wrapper.pb.h"

class Server
{
private:
  static const int MaxDataGramSize = 65536;
  char *in_buffer;
  int port;
  std::string address;
  std::string inter_face;
  Net::UDP multiCast;
  QMutex mutex;
  long int frameNo;
  int tcapture;
  SSL_DetectionFrame *dframe;
  SSL_DetectionBall *ball;
  SSL_DetectionRobot *bot[2*Simulator::BOT_MAX];

public:
  SSL_DetectionFrame *nframe;
  SSL_GeometryData * gdata;

  Server(int port=Simulator::PORT, std::string address=Simulator::ADDRESS, std::string inter_face=Simulator::INTER_FACE);
  ~Server();
  bool openMulticast(bool block=false);
  void closeMulticast();
  bool send(const SSL_WrapperPacket & packet);
  bool send(const SSL_DetectionFrame & frame);
  bool send(const SSL_GeometryData & geometry);
  bool receive(SSL_WrapperPacket &packet);
  void updateBot(int team,int botNo,float x,float y,float orientation);
  void updateBall(float x,float y);
  bool send_detection(double tcap,double tnow);
};
#endif