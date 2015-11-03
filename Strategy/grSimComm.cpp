#include <cstdio>
#include "../rbSimulator/config.h"
#include "grSimComm.h"
#include "cs.hpp"
#include "logger.h"
#include "grSim_Packet.pb.h"
#include "grSim_Commands.pb.h"
#include "grSim_Replacement.pb.h"
#include "sslDebug_Data.pb.h"

using namespace Util;

namespace HAL
{
  GrSimComm::GrSimComm()
  {
    if (reconnectUDP())
    {
      for (int i = 0; i < Strategy::HomeTeam::SIZE; ++i)
      {
        sendCommand(i, 0, 0, 0, 0, false);
      }
      Logger::toStdOut("Robot command listen UDP network successfully configured. (Multicast address: %s:%d)\n", 
                        Simulator::ADDRESS, Simulator::COMMAND_PORT);
    }
    else
    {
      Logger::toStdOut("Error : Could not configure the Robot command UDP network\n");
    }
  }

  bool GrSimComm::reconnectUDP()
  {
    udpsocket.close();
    bool flag = _addr.setHost(Simulator::ADDRESS, Simulator::COMMAND_PORT);
    return (udpsocket.open(Simulator::COMMAND_PORT, false, false, false) && flag);
  }

  void GrSimComm::disconnectUDP()
  {
    udpsocket.close();
  }

  GrSimComm::~GrSimComm()
  {
    disconnectUDP();
  }

  void GrSimComm::sendCommand(int   botID,
                              float v_x,
                              float v_y,
                              float v_t,
                              float kickPower,
                              bool  dribble)
  {
	//Logger::toStdOut("Bot: %d, %f, %f, %f, %d\n", botID, v_x, v_y, v_t, kickPower, (int)dribble);
    commCS.enter();
    grSim_Packet packet;
    packet.mutable_commands()->set_isteamyellow(Strategy::HomeTeam::COLOR == Simulator::YELLOW_TEAM);
    packet.mutable_commands()->set_timestamp(0.0);
    grSim_Robot_Command* command = packet.mutable_commands()->add_robot_commands();
    command->set_id(botID);
    command->set_wheelsspeed(false);
    command->set_veltangent(v_y/1000.0f);  // Unit of length in Strategy used is mm but it is m in grSim
    command->set_velnormal(-v_x/1000.0f);  // Unit of length in Strategy used is mm but it is m in grSim
    command->set_velangular(v_t);
    command->set_kickspeedx(kickPower);
    command->set_kickspeedz(0);         // Chip-kicker disabled
    command->set_spinner(dribble);

    // Adding debug info to the command packet
    while (debug_circles.empty() == false)
    {
      Debug_Circle circle = debug_circles.front();
      debug_circles.pop_front();
      packet.mutable_debuginfo()->add_circle()->CopyFrom(circle);
    }

    while (debug_lines.empty() == false)
    {
      Debug_Line line = debug_lines.front();
      debug_lines.pop_front();
      packet.mutable_debuginfo()->add_line()->CopyFrom(line);
    }
    /*
    Debug_AdjustBot botpos;
    Debug_AdjustBall ballpos;
    botpos.set_x(1000);
    botpos.set_y(1000);
    botpos.set_vx(0);
    botpos.set_vy(0);
    botpos.set_vz(0);
    botpos.set_team(0);
    botpos.set_id(0);
    botpos.set_dir(0);
    packet.mutable_debuginfo()->add_botpos()->CopyFrom(botpos);
    */
    std::string s;
    packet.SerializeToString(&s);
    udpsocket.send((void*)s.c_str(), s.length(), _addr);
    commCS.leave();
  }
} // namespace HAL
