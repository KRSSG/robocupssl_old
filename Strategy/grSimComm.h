/* This header file contains the definition of class SimComm  which inherits Comm class.
 * This class is used to  assign commands to the all the bots of the team for the 3D simulator.
 */

#ifndef SIM3D_COMM_H
#define SIM3D_COMM_H

#include <list>
#include "comm.h"
#include "netraw.h"
#include "sslDebug_Data.pb.h"

// Forward Declarations
namespace Util
{
  class CS;
}

namespace HAL
{
  class GrSimComm : public Comm
  {
  private:
    Net::UDP                udpsocket;
    Net::Address            _addr;
    std::list<Debug_Circle> debug_circles;
    std::list<Debug_Line>   debug_lines;
    
    bool reconnectUDP();
    void disconnectUDP();

  public:
    GrSimComm();

    ~GrSimComm();

    void sendCommand(int   botID,
                     float v_x,
                     float v_y,
                     float v_t,
                     float kickPower,
                     bool  dribble);
                     
    inline void addCircle(int x, int y, unsigned int radius)
    {
      Debug_Circle circle;
      circle.set_x(x);
      circle.set_y(y);
      circle.set_radius(radius);
      debug_circles.push_back(circle);
    }
    
    inline void addLine(int x1, int y1, int x2, int y2)
    {
      Debug_Line line;
      line.set_x1(x1);
      line.set_y1(y1);
      line.set_x2(x2);
      line.set_y2(y2);
      debug_lines.push_back(line);
    }
  };
}

#endif // SIM3D_COMM_H
