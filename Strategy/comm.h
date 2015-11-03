#ifndef COMM_H
#define COMM_H

// Forward Declarations
namespace Util
{
  class CS;
}

namespace HAL
{
  class Comm
  {
  private:
    // To ensure only one instance of Comm's derived class is created, the following flag is used
    static bool initializedOnce;

  protected:
    static Util::CS commCS;

  public:
    Comm();

    virtual ~Comm();

    /* This function must be implemented in the derived classes.
     * Remember to guard the entire function body with the CS object commCS
     * otherwise the result will be undefined and communication protocols
     * may break down
     */
    virtual void sendCommand(int   botID,           // valid bot ID
                             float v_x,             // in mm/sec
                             float v_y,             // in mm/sec
                             float v_t,             // in rad/sec
                             float kickPower,       // in the range [0,1]
                             bool  dribble) = 0;    // on(true) or off(false)
  }; // class Comm
} // namespace HAL

#endif // COMM_H
