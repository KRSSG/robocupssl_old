#include "Server.h"

using namespace Simulator;

Server::Server(int _port, std::string _address, std::string _inter_face){
  address=_address;
  port=_port;
  inter_face=_inter_face;
  in_buffer=new char[65536];
  frameNo=1;
  openMulticast();
  dframe=new SSL_DetectionFrame();
  ball=dframe->add_balls();
  ball->set_area(BALL_AREA);
  ball->set_pixel_x(BALL_PIXEL_X);
  ball->set_pixel_y(BALL_PIXEL_Y);
  ball->set_confidence(1);
  ball->set_x(0);
  ball->set_y(0);
  for(int i=0;i<BOT_MAX;++i)
  {
    bot[i]=dframe->add_robots_blue();
    bot[i]->set_robot_id(i);
    bot[i]->set_pixel_x(BOT_PIXEL_X);
    bot[i]->set_pixel_y(BOT_PIXEL_Y);
    bot[i]->set_confidence(1);
    bot[i]->set_x(0);
    bot[i]->set_y(0);
    bot[i]->set_orientation(0);
  }
  for(int i=0;i<BOT_MAX;++i)
  {
    bot[i+BOT_MAX]=dframe->add_robots_yellow();
    bot[i+BOT_MAX]->set_robot_id(i);
    bot[i+BOT_MAX]->set_pixel_x(BOT_PIXEL_X);
    bot[i+BOT_MAX]->set_pixel_y(BOT_PIXEL_Y);
    bot[i+BOT_MAX]->set_confidence(1);
    bot[i+BOT_MAX]->set_x(0);
    bot[i+BOT_MAX]->set_y(0);
    bot[i+BOT_MAX]->set_orientation(0);
  }
}
Server::~Server()
{
  delete in_buffer;
  delete dframe;
}
bool Server::openMulticast(bool block)
{
  closeMulticast();
  if(!(multiCast.open(port,true,true,block)))
  {
    fprintf(stderr,"Opening port : %d failed\n",port);
    fflush(stderr);
    return false;
  }
  Net::Address _address,_interface;
  if(!(_address.setHost(address.c_str(),port)))
  {
    fprintf(stderr,"setHost(address,port) failed\n");
    fflush(stderr);
    return false;
  }
  if(inter_face.length()>0)
  {if(!(_interface.setHost(inter_face.c_str(),port)))
  {
    fprintf(stderr,"setHost(interface,port) failed\n");
    fflush(stderr);
    return false;
  }
  }
  else{
    _interface.setAny();
  }
  if(!(multiCast.addMulticast(_address,_interface)))
  {
    fprintf(stderr,"adding Multicast failed\n");
    fflush(stderr);
    return false;
  }
  return true;
}
void Server::closeMulticast()
{
  multiCast.close();
}

void Server::updateBot(int team, int botNo, float x, float y, float orientation)
{
  bot[botNo]->set_x(x);
  bot[botNo]->set_y(y);
  bot[botNo]->set_orientation(-orientation);
}

void Server::updateBall(float x,float y)
{
  ball->set_x(x);
  ball->set_y(y);
}
bool Server::send_detection(double t,double tnow)
{
  dframe->set_frame_number(frameNo++);
  dframe->set_camera_id(0);
  dframe->set_t_capture(t);
  dframe->set_t_sent(tnow);
  return send(*dframe);
}
bool Server::send(const SSL_WrapperPacket & packet) {
  std::string buffer;
  packet.SerializeToString(&buffer);
  Net::Address multiaddr;
  multiaddr.setHost(address.c_str(),port);
  bool result;
  mutex.lock();
  result=multiCast.send(buffer.c_str(),buffer.length(),multiaddr);
  mutex.unlock();
  if (result==false) {
    fprintf(stderr,"Sending UDP datagram failed (maybe too large?). Size was: %lu byte(s)\n",buffer.length());
  }
  return(result);
}

bool Server::send(const SSL_DetectionFrame & frame) {
  SSL_WrapperPacket pkt;
  nframe = pkt.mutable_detection();
  nframe->CopyFrom(frame);
  return send(pkt);
}

bool Server::send(const SSL_GeometryData & geometry) {
  SSL_WrapperPacket pkt;
  gdata = pkt.mutable_geometry();
  gdata->CopyFrom(geometry);
  return send(pkt);
}

bool Server::receive(SSL_WrapperPacket & packet) {
  Net::Address src;
  int r=0;
  r = multiCast.recv(in_buffer,MaxDataGramSize,src);
  if (r>0) {
    fflush(stdout);
    return packet.ParseFromArray(in_buffer,r);
  }
  return false;
}