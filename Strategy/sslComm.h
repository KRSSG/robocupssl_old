#ifndef SSL_COMM_H
#define SSL_COMM_H

#include "comm.h"
#include "rbCommDef.h"
#include "serial.h"

namespace Util
{
  class CS;
}

namespace HAL
{
  class SSLComm : public Comm
  {
  private:
    Serial    sPort;
    SSLPacket command;

  public:
    SSLComm();

    ~SSLComm();

    void sendCommand(int   botID,
                     float v_x,
                     float v_y,
                     float v_t,
                     float kickPower,
                     bool  dribble);
		// Adding dummy functions for compatibity with other codes.
		inline void addCircle(int x, int y, unsigned int radius) {}
		inline void addLine(int x1, int y1, int x2, int y2)      {}
  }; // class SSLComm
} // namespace HAL

#endif // SSL_COMM_H
