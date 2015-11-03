#ifndef INCL_RbSimulator_H
#define INCL_RbSimulator_H

#include <winsock2.h>
#include <QtGui/QMainWindow>
#include "ui_RbSimulator.h"
#include "graphicsItems.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QTimer>
#include <QGLWidget>
#include <ctime>
#include <QString>
#include <QDateTIme>
#include "server.h"
#include "config.h"
#include "logplayer.h"
#include <QFileDialog>
#include "entityInfo.h"
#include "RbCentral.h"
#include "physxEngineMain.h"
#include "rbCommDef.h"

namespace Simulator
{
  class RbSimulator : public QMainWindow
  {
  private:
    Util::Shmem *shmemDebug;
    HAL::SimPacket     *DebugCommand;

    Q_OBJECT

  public:
    RbSimulator(Simulator::RbCentral* rbCen_, QWidget* parent = 0, Qt::WFlags flags = 0);
    ~RbSimulator();
    void newpos(int,int,float,float,float);
    void readNext();
    void goToBeg();
    void goToPoint(int x);
    GCanvas* addCanvas(int r,int g,int b);
    int addEle(HAL::CanvasColor c, HAL::CanvasItem& ele);
    bool PAUSED;
    bool status_simu;
    bool logIsPlaying;

  public slots:
    void moveall();
    void startAgain();
    void stopNow();
    void setBot(int team, int botNo, float x, float y, float orientation);
    void setBall(float x,float y);
    void contactClient();
    void switchToMonitor();
    void switchToSimulator();
    void startLogRecord();
    void startLogPlay();
    void readLog();
    void writeLog();
    void cleanLog();
    void chooseFile();
    void on_logPauseBtn_clicked();
    void on_logResumeBtn_clicked();
    void on_logRecordStop_clicked();
    void on_fpsSlider_sliderMoved(int);
    void setLogFile(const char* f);
    void recordNearestObject();

  private:
    QMutex locker;
    QTime tnow;
    double tcapture;
    SSL_WrapperPacket recvPacket;
    logplayer player;
    Simulator::RbCentral* rbCen;
    GCanvas* redC,*blueC,*blackC,*whiteC;
    //-----------------------------------------------------------------------------------------------------
    float x[2*BOT_MAX];
    float y[2*BOT_MAX];
    float xs[2*BOT_MAX];
    float ys[2*BOT_MAX];
    float rot[2*BOT_MAX];
    float rots[2*BOT_MAX];
    float ballX;
    float ballY;
    int currentFPS;
    //-----------------------------------------------------------------------------------------------------
    
    
    //--------  GUI VARIABLES  ----------------------
    QGLWidget *qGL;
    QLabel *b_bot[BOT_MAX];
    QLabel *y_bot[BOT_MAX];
    QLabel *bx_bot[BOT_MAX];
    QLabel *by_bot[BOT_MAX];
    QLabel *bo_bot[BOT_MAX];
    QLabel *yx_bot[BOT_MAX];
    QLabel *yy_bot[BOT_MAX];
    QLabel *yo_bot[BOT_MAX];
    QGraphicsScene *simu_scene;
    Gbot *BOT[2*BOT_MAX];
    Gball *BALL;
    Gfield *FIELD;
    QTimer *logWriter;
    QTimer *logReader;
    QTimer *timerSend;
    Server *Game;
    //-----------------------------------------------
    Ui::RbSimulatorClass ui;
    
    void setLogBot(int team, int botNo,float x,float y,float orientation);
    void setLogBall(float x,float y);
  };
}
#endif // rbSimulator_H
