#include <QTime>
#include "RbSimulator.h"
#include "qlocale.h"

using namespace Simulator;
using namespace Strategy;
using namespace HAL;

RbSimulator::RbSimulator(Simulator::RbCentral* rbCen_,QWidget *parent, Qt::WFlags flags): QMainWindow(parent, flags)
{
  tcapture=0;
  status_simu=true;
  logIsPlaying=false;
  PAUSED=true;
  tnow.start();
  ui.setupUi(this);
  rbCen=rbCen_;
  ui.port_lab->setText(QString::number((int)(VISION_PORT)));
  ui.address_lab->setText(QString(ADDRESS));
  ui.ballrad_lab->setText(QString::number(_BALL_RADIUS));
  ui.interface_lab->setText(QString(INTER_FACE));
  ui.botrad_lab->setText(QString::number(_BOT_RADIUS));
  ui.nbots_lab->setText(QString::number(BOT_MAX));
  ui.fWidth_lab->setText(QString::number(field_width));
  ui.fLength_lab->setText(QString::number(field_length));
  ui.gWidth_lab->setText(QString::number(goal_width));
  ui.gDepth_lab->setText(QString::number(goal_depth));
  ui.defRadius_lab->setText(QString::number(defense_radius));
  ui.defStetch_lab->setText(QString::number(defense_stretch));
  ui.graphicsView->setFixedSize(QSize((2*boundary_width+field_length)*scaleFactor+10,(2*boundary_width+field_width)*scaleFactor+10));
  Game=new Server();
  BALL=new Gball(_BALL_RADIUS);
  BALL->setPos(0,0);
  connect(ui.startbtn,SIGNAL(clicked()),this,SLOT(startAgain()));
  connect(ui.stopbtn,SIGNAL(clicked()),this,SLOT(stopNow()));
  simu_scene=new QGraphicsScene(ui.graphicsView);
  simu_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  simu_scene->setSceneRect(QRectF(-boundary_width-field_length/2,-boundary_width-field_width/2,2*boundary_width+field_length,2*boundary_width+field_width));
  FIELD=new Gfield(*rbCen);
  simu_scene->addItem(FIELD);
  simu_scene->addItem(BALL);
  FIELD->setPos(-field_length/2,-field_width/2);
//  connect(simu_scene, SIGNAL(clicked()), this, SLOT(recordNearestObject());
  
  redC=addCanvas(255,0,0);
  blueC=addCanvas(0,0,255);
  whiteC=addCanvas(255,255,255);
  blackC=addCanvas(0,0,0);
  
  for(int botn=0;botn<2*BOT_MAX;botn++)
  {
    BOT[botn]=new Gbot(*(rbCen->posInfo), botn%BOT_MAX, botn/BOT_MAX);
    simu_scene->addItem(BOT[botn]);
    /*only for testing*/
    x[botn]=y[botn]=botn*100;
    xs[botn]=5+rand()%200/100;
    ys[botn]=5+rand()%200/50;
    rot[botn]=(rand()%360)/20;
    rots[botn]=(rand()%30)/20;
    BOT[botn]->setPos(x[botn],-y[botn]);
    BOT[botn]->setRotation(rot[botn]*16);
    //------------------*/
  }
  ballX=0;
  ballY=0;
  b_bot[BOT_MAX];
  y_bot[BOT_MAX];
  for(int botn=0;botn<BOT_MAX;botn++)
  {
    b_bot[botn] = new QLabel(ui.layoutWidget3);
    ui.gridLayout_3->addWidget(b_bot[botn], botn+1, 0, 1, 1);
    b_bot[botn]->setText(QString("BOT"+QString::number(botn)));
    bx_bot[botn] = new QLabel(ui.layoutWidget3);
    ui.gridLayout_3->addWidget(bx_bot[botn], botn+1, 1, 1, 1);
    bx_bot[botn]->setText(QString("X"));
    by_bot[botn] = new QLabel(ui.layoutWidget3);
    ui.gridLayout_3->addWidget(by_bot[botn], botn+1, 2, 1, 1);
    by_bot[botn]->setText(QString("Y"));
    bo_bot[botn] = new QLabel(ui.layoutWidget3);
    ui.gridLayout_3->addWidget(bo_bot[botn], botn+1, 3, 1, 1);
    bo_bot[botn]->setText(QString("Orient"));


    y_bot[botn] = new QLabel(ui.layoutWidget2);
    ui.gridLayout->addWidget(y_bot[botn], botn+1, 0, 1, 1);
    y_bot[botn]->setText(QString("BOT"+QString::number(botn)));
    yx_bot[botn] = new QLabel(ui.layoutWidget2);
    ui.gridLayout->addWidget(yx_bot[botn], botn+1, 1, 1, 1);
    yx_bot[botn]->setText(QString("X"));
    yy_bot[botn] = new QLabel(ui.layoutWidget2);
    ui.gridLayout->addWidget(yy_bot[botn], botn+1, 2, 1, 1);
    yy_bot[botn]->setText(QString("X"));
    yo_bot[botn] = new QLabel(ui.layoutWidget2);
    ui.gridLayout->addWidget(yo_bot[botn], botn+1, 3, 1, 1);
    yo_bot[botn]->setText(QString("Orient"));
  }
  currentFPS=30;
  ui.fpsLbl->setText(QString("Speed:"));
  qGL=new QGLWidget(QGLFormat(QGL::SampleBuffers), this);
  ui.graphicsView->setViewport(qGL);
  simu_scene->setBackgroundBrush(QBrush(QColor(40,255,0,255)));
  ui.fileName_text->setText(QString("temp.log"));
  ui.graphicsView->setScene(simu_scene);
  ui.graphicsView->scale(scaleFactor,scaleFactor);
  ui.graphicsView->show();
  
  ui.defaultValues_dock->hide();
  ui.blue_dock->hide();
  ui.yellow_dock->hide();
  
  connect(ui.actionTeam_Yellow,SIGNAL(triggered()),ui.yellow_dock,SLOT(show()));
  connect(ui.actionTeam_Blue,SIGNAL(triggered()),ui.blue_dock,SLOT(show()));
  connect(ui.actionRandom_Motion,SIGNAL(triggered()),ui.random_dock,SLOT(show()));
  connect(ui.actionDefaut_Values,SIGNAL(triggered()),ui.defaultValues_dock,SLOT(show()));
  connect(ui.actionLog_Player,SIGNAL(triggered()),ui.logPlayer,SLOT(show()));
  connect(ui.actionSwitch_to_Monitor,SIGNAL(triggered()),this,SLOT(switchToMonitor()));
  connect(ui.actionSwitch_to_Simulator,SIGNAL(triggered()),this,SLOT(switchToSimulator()));
  connect(ui.logRecord_lab,SIGNAL(clicked()),this,SLOT(startLogRecord()));
  connect(ui.logPlay_lab,SIGNAL(clicked()),this,SLOT(startLogPlay()));
  connect(ui.select_btn,SIGNAL(clicked()),this,SLOT(chooseFile()));
  connect(ui.logRecordClean_btn,SIGNAL(clicked()),this,SLOT(cleanLog()));

  //This timer is for sending data to the Client
  timerSend=new QTimer(this);
  connect (timerSend,SIGNAL(timeout()),this,SLOT(contactClient()));
  timerSend->start(1000/SEND_RATE);//sending data at 60fps

  //log Writer and reader Timer only one of them is executed at a time.
  logWriter=new QTimer(this);
  connect (logWriter,SIGNAL(timeout()),this,SLOT(writeLog()));
  logReader=new QTimer(this);
  connect (logReader,SIGNAL(timeout()),this,SLOT(readLog()));
}

RbSimulator::~RbSimulator()
{  
  timerSend->stop();
  logReader->stop();
  logWriter->stop();
  delete(blackC);
  delete(whiteC); 
  delete(redC);
  delete(blueC);
  delete(Game);
  for(int i=0; i<=2*BOT_MAX; ++i)
  {
    delete(BOT[i]);
  }
}

void RbSimulator::setBot(int team,int botNo,float x ,float y,float rot)
{
  if(!ui.showLogCheck->isChecked())
  {
    // ----- culprit lines which are eating up the processor-----
    BOT[botNo]->setPos(x, -y);
    BOT[botNo]->setRotation(-rot*180.0f/3.14159f);
    // ----------------------------------------------------------
    tcapture=(double)(tnow.elapsed())/1000.0;
    if(team && ui.blue_dock->isVisible())
    {
      bx_bot[botNo]->setText(QString::number(x));
      by_bot[botNo]->setText(QString::number(y));
      bo_bot[botNo]->setText(QString::number(rot*180.0f/3.14159f));
    }
    else if(!team && ui.yellow_dock->isVisible())
    {
      yx_bot[botNo]->setText(QString::number(x));
      yy_bot[botNo]->setText(QString::number(y));
      yo_bot[botNo]->setText(QString::number(rot*180.0f/3.14159f));
    }
  }
  float pi = 3.14159265358979323f;
  float angle = fmod(-rot,2*pi);
  if(angle>pi)
      angle -= 2*pi;
  else if(angle<-pi)
      angle += 2*pi;
  Game->updateBot(team, botNo, x, y,angle);
}

void RbSimulator::setBall(float x,float y)
{
  if(!ui.showLogCheck->isChecked())
    BALL->setPos(x,-y);
  Game->updateBall(x,y);  
}
void RbSimulator::contactClient()
{ 
  if(status_simu){
    rbCen->run();
    for (int i=0; i<BOT_MAX; ++i)
    {
      setBot(TeamID::HOME, i, rbCen->posInfo->bluePos[i].x*1000, rbCen->posInfo->bluePos[i].y*1000, rbCen->posInfo->blueAngle[i]);
      setBot(TeamID::AWAY, BOT_MAX + i, rbCen->posInfo->yellowPos[i].x*1000, rbCen->posInfo->yellowPos[i].y*1000, rbCen->posInfo->yellowAngle[i]);
    }
    setBall(rbCen->posInfo->ballPos.x*1000, rbCen->posInfo->ballPos.y*1000);
    Game->send_detection(tcapture,(double)(tnow.elapsed())/1000.0);
    }
  else
  {
    if(Game->receive(recvPacket))
    {
      if(recvPacket.has_detection())
      {
        SSL_DetectionFrame detection = recvPacket.detection();

        //printf("-[Detection Data]-------\n");
        ////Frame info:
        //printf("Camera ID=%d FRAME=%d T_CAPTURE=%.4f\n",detection.camera_id(),detection.frame_number(),detection.t_capture());

        //printf("SSL-Vision Processing Latency                   %7.3fms\n",(detection.t_sent()-detection.t_capture())*1000.0);
        //printf("Network Latency (assuming synched system clock) %7.3fms\n",(t_now-detection.t_sent())*1000.0);
        //printf("Total Latency   (assuming synched system clock) %7.3fms\n",(t_now-detection.t_capture())*1000.0);
        int ballsNum = detection.balls_size();
        int blueNum =  detection.robots_blue_size();
        int yellowNum =  detection.robots_yellow_size();
        if(ballsNum>1)
        {
        }
        blueNum=(blueNum>BOT_MAX)?BOT_MAX:blueNum;
        yellowNum=(yellowNum>BOT_MAX)?BOT_MAX:yellowNum;
        /*printf("%d %d %d\n",balls_n,robots_blue_n,robots_yellow_n);*/
        //Ball info:
        for (int i = 0; i < ballsNum; ++i) 
        {
          SSL_DetectionBall ball = detection.balls(i);
          /*printf("-Ball (%2d/%2d): CONF=%4.2f POS=<%9.2f,%9.2f> ", i+1, balls_n, ball.confidence(),ball.x(),ball.y());
          if (ball.has_z()) {
              printf("Z=%7.2f ",ball.z());
          } else {
              printf("Z=N/A   ");
          }
          printf("RAW=<%8.2f,%8.2f>\n",ball.pixel_x(),ball.pixel_y());*/
          setBall(ball.x(),ball.y());
        }

        //Blue robot info:
        for (int i = 0; i < blueNum; ++i) 
        {
          SSL_DetectionRobot robot = detection.robots_blue(i);
          setBot(TeamID::HOME, i,robot.x(),robot.y(),robot.orientation());
        }

        //Yellow robot info:
        for (int i = 0; i < yellowNum; ++i) 
        {
          SSL_DetectionRobot robot = detection.robots_yellow(i);
          setBot(TeamID::AWAY,i+BOT_MAX,robot.x(),robot.y(),robot.orientation());
        }
        ui.graphicsView->update();
      }
    }
  }
}

void RbSimulator::moveall()
{
  
}

void RbSimulator::startAgain()
{
  PAUSED=false;
}

void RbSimulator::stopNow()
{
  PAUSED=true;
}

void RbSimulator::switchToMonitor()
{
  status_simu=false;
  Game->openMulticast(true);
}

void RbSimulator::switchToSimulator()
{
  status_simu=true;
  Game->openMulticast();
}

void RbSimulator::setLogFile(const char* f)
{
  player.open(f, "w");
}
void RbSimulator::startLogRecord()
{
  QString fileName = QDateTime::currentDateTime().toString().replace(' ', '_').replace(':','_').append(QString(".log"));
  ui.fileName_text->setText(fileName);
  setLogFile(fileName.toStdString().c_str());
  logReader->stop();
  logWriter->start(1000/30);
  logIsPlaying=false;
  ui.statusLbl->setText(QString("Recording ..."));
}

void RbSimulator::startLogPlay()
{
  on_logRecordStop_clicked();
  ui.showLogCheck->setChecked(true);
  player.open(ui.fileName_text->text().toAscii().data(),"r");
  logReader->start(1000/currentFPS);
  logIsPlaying=true;
}

void RbSimulator::writeLog()
{
  player.writeBall(rbCen->posInfo->ballPos.x, rbCen->posInfo->ballPos.y);
  for(int i=0;i<BOT_MAX;++i)
  {
    player.writeBot(rbCen->posInfo->bluePos[i].x, rbCen->posInfo->bluePos[i].y, rbCen->posInfo->blueAngle[i]);
  }
  for(int i=0;i<BOT_MAX;++i)
  {
    player.writeBot(rbCen->posInfo->yellowPos[i].x, rbCen->posInfo->yellowPos[i].y, rbCen->posInfo->yellowAngle[i]);
  }
}

void RbSimulator::cleanLog()
{
  player.close();
  player.open(ui.fileName_text->text().toAscii().data(),"w");
}

void RbSimulator::chooseFile()
{
    ui.fileName_text->setText(QFileDialog::getSaveFileName(this,"Select a logFile","*.log","Log Files(*.log)"));
}

void RbSimulator::readLog()
{
  float bx,by;
  float botx,boty,ori;
  player.readBall(&bx,&by);
  setLogBall(bx,by);
  for(int i=0;i<2*BOT_MAX;++i)
  {
    if(player.readBot(&botx,&boty,&ori))
      setLogBot(i/BOT_MAX,i%BOT_MAX,botx,boty,ori);
    else
      on_logPauseBtn_clicked();
  }
}

void RbSimulator::on_logRecordStop_clicked()
{
  player.close();
  logWriter->stop();
  ui.statusLbl->setText(QString("Paused"));
}

void RbSimulator::on_logPauseBtn_clicked()
{
  if(logIsPlaying)
  {
    logReader->stop();
  }
}

void RbSimulator::on_logResumeBtn_clicked()
{
  if(logIsPlaying)
  {
    logReader->start(1000/currentFPS);
  }
}
void RbSimulator::setLogBall(float x, float y)
{
  if(ui.showLogCheck->isChecked())
    BALL->setPos(x*1000,-y*1000);
}
void RbSimulator::setLogBot(int team, int botNo, float x, float y, float rotx)
{
  if(ui.showLogCheck->isChecked())
  {
    BOT[team*BOT_MAX+botNo]->setPos(x*1000,-y*1000);
    BOT[team*BOT_MAX+botNo]->setRotation(rotx*180.0f/3.1415f);
    tcapture=(double)(tnow.elapsed())/1000.0;
    if(team && ui.blue_dock->isVisible())
    {
      bx_bot[botNo]->setText(QString::number(x));
      by_bot[botNo]->setText(QString::number(y));
      bo_bot[botNo]->setText(QString::number(rotx));
    }
    else if(!team && ui.yellow_dock->isVisible())
    {
      yx_bot[botNo]->setText(QString::number(x));
      yy_bot[botNo]->setText(QString::number(y));
      yo_bot[botNo]->setText(QString::number(rotx));
    }
  }
}
void RbSimulator::on_fpsSlider_sliderMoved(int val)
{
  currentFPS=val;
  logReader->setInterval(1000/currentFPS);
}
GCanvas* RbSimulator::addCanvas(int r,int g,int b)
{
  GCanvas* can=new GCanvas(r,g,b);
  can->setPos(0,0);
  simu_scene->addItem(can);
  return can;
}

int RbSimulator::addEle(CanvasColor c, CanvasItem& ele) 
{
  switch (c)
  {
    case CanvasColor::BLACK:
      return blackC->addEle(ele);
      break;
    case CanvasColor::WHITE:
      return whiteC->addEle(ele);
      break;
    case CanvasColor::RED:
      return redC->addEle(ele);
      break;
    case CanvasColor::BLUE:
      return blueC->addEle(ele);
      break;
  }
  return -1;
}

void RbSimulator::recordNearestObject()
{
}
