#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QMimeData>
#include <QDrag>
#include <QMutex>
#include "graphicsItems.h"

using namespace PhysxEngine;
using namespace Simulator;
using namespace HAL;

Gbot::Gbot(PhysxEngine::PosInfo &posInfo, int botID, int team,int radius):
pixmap(0.4*_BOT_RADIUS, 0.4*_BOT_RADIUS),botID(botID)
{
  setToolTip(QString("BOT:%1").arg(QString::number(botID)));
  QCursor cur = Qt::OpenHandCursor; 
  setCursor(cur);
  setAcceptedMouseButtons(Qt::LeftButton);
  BOT_RADIUS=radius;
  botID = botID;
  teamNo=team;
  QPainter painter(&pixmap);
  painter.scale(0.2,0.2);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(_BOT_RADIUS,_BOT_RADIUS);
  paint(&painter, 0, 0);
  painter.end();
  this->posInfo = &posInfo;
}

QRectF Gbot::boundingRect() const
{
  return QRectF(-1 -BOT_RADIUS, -1-BOT_RADIUS, 2+2*BOT_RADIUS, 2+2*BOT_RADIUS);
}

void Gbot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  
  QRadialGradient radial(0,0,BOT_RADIUS);
  if(teamNo==BLUE)
  {
  radial.setColorAt(0,QColor(255,255,255,255));
  radial.setColorAt(0.5,QColor(0,0,255,255));
  }
  else
  {
  radial.setColorAt(0,QColor(0,0,0,255));
  radial.setColorAt(0.5,QColor(255,255,0,255));
  }
  painter->setPen(Qt::NoPen);
  painter->setBrush(radial);
  QPainterPath *path=new QPainterPath(QPointF((float)BOT_RADIUS/1.415f,-(float)BOT_RADIUS/1.415f));
  path->arcTo(QRectF(QPointF(-BOT_RADIUS,-BOT_RADIUS),QPointF(BOT_RADIUS,BOT_RADIUS)),45,270);
  path->lineTo(QPointF((float)BOT_RADIUS/1.415f,-(float)BOT_RADIUS/1.415f));
  path->closeSubpath();
  painter->drawPath(*path);
  delete(path);
}
void Gbot::mousePressEvent(QGraphicsSceneMouseEvent *evt)
 {
     setCursor(Qt::ClosedHandCursor);
 }
void Gbot::mouseReleaseEvent(QGraphicsSceneMouseEvent *evt)
 {
     setCursor(Qt::OpenHandCursor);
 }
void Gbot::mouseMoveEvent(QGraphicsSceneMouseEvent *evt)
{
    QDrag *drag = new QDrag(evt->widget());
    QMimeData *mime =  new QMimeData;
    drag->setMimeData(mime);
    mime->setText(QString("BOT %1 %2").arg(QString::number(teamNo), QString::number(botID)));
    setCursor(Qt::OpenHandCursor);
    drag->setPixmap(pixmap);
    drag->exec();
}
Gbot::~Gbot()
{
}
Gfield::Gfield(Simulator::RbCentral &rbCen)
{     
    setAcceptDrops(true);
    this->posInfo = rbCen.posInfo;
    this->rbCen = &rbCen;
}

QRectF Gfield::boundingRect() const
{
  return QRectF(-boundary_width,-boundary_width,field_length+2*boundary_width,field_width+2*boundary_width);
}

void Gfield::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
  painter->setPen(QPen(Qt::black, line_width, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(QRectF(QPointF(-boundary_width,-boundary_width),QPointF(field_length+boundary_width,field_width+boundary_width)));
  painter->setPen(QPen(Qt::black, line_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(QRectF(QPointF(0,0),QPointF(field_length,field_width)));
  painter->setPen(QPen(Qt::black, goal_wall_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawRect(QRectF(QPointF(-goal_depth,field_width/2-goal_width/2),QPointF(0,field_width/2+goal_width/2)));
  painter->drawRect(QRectF(QPointF(field_length,field_width/2-goal_width/2),QPointF(field_length+goal_depth,field_width/2+goal_width/2)));
  painter->setPen(QPen(Qt::black, line_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  painter->drawLine(field_length/2,0,field_length/2,field_width);
  painter->drawEllipse(field_length/2-center_circle_radius,field_width/2-center_circle_radius,2*center_circle_radius,2*center_circle_radius);
  painter->drawArc(-defense_radius,field_width/2-defense_radius-defense_stretch/2,2*defense_radius,2*defense_radius,0,90*16);
  painter->drawArc(-defense_radius,field_width/2-defense_radius+defense_stretch/2,2*defense_radius,2*defense_radius,270*16,90*16);
  painter->drawLine(defense_radius,field_width/2-defense_stretch/2,defense_radius,field_width/2+defense_stretch/2);
  painter->drawArc(field_length-defense_radius,field_width/2-defense_radius-defense_stretch/2,2*defense_radius,2*defense_radius,90*16,90*16);
  painter->drawArc(field_length-defense_radius,field_width/2-defense_radius+defense_stretch/2,2*defense_radius,2*defense_radius,180*16,90*16);
  painter->drawLine(field_length-defense_radius,field_width/2-defense_stretch/2,field_length-defense_radius,field_width/2+defense_stretch/2);
}

void Gfield::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText()) {
      event->setAccepted(true);
      startPoint = event->pos();
      update();
  } else {
      event->setAccepted(false);
  }
}
void Gfield::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{     
    Q_UNUSED(event);
    update();
}
void Gfield::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasText())
    {
        QString text = event->mimeData()->text();
        QStringList li = text.split(' ');
        if(li[0].compare(QString("BOT"))==0)
        {
            QMutex mutex;
            
            switch(li[1].toInt())
            {
            case BLUE:
                rbCen->ready = false;
                posInfo->bluePos[li[2].toInt()].x+=(event->pos().x() - startPoint.x())/1000.0f;
                posInfo->bluePos[li[2].toInt()].y-=(event->pos().y() - startPoint.y())/1000.0f;
                if(posInfo->checkBounds() && posInfo->checkOverlap())
                    rbCen->engine->updateWorld();
                rbCen->ready = true;
                break;
            case YELLOW:
                rbCen->ready = false;
                posInfo->yellowPos[li[2].toInt()].x+=(event->pos().x() - startPoint.x())/1000.0f;
                posInfo->yellowPos[li[2].toInt()].y-=(event->pos().y() - startPoint.y())/1000.0f;
                if(posInfo->checkBounds() && posInfo->checkOverlap())
                    rbCen->engine->updateWorld();
                rbCen->ready = true;
                break;
            }
        }else if(li[0].compare(QString("BALL"))==0)
        {
            rbCen->ready=false;
            posInfo->ballPos.x += (event->pos().x() - startPoint.x())/1000.0f;
            posInfo->ballPos.y -= (event->pos().y() - startPoint.y())/1000.0f;
            if(posInfo->checkBounds() && posInfo->checkOverlap())
                rbCen->engine->updateWorld();
            rbCen->ready = true;
        }
        update();
    }
}
Gball::Gball(int rad=Simulator::_BALL_RADIUS):
pixmap(0.4*_BALL_RADIUS, 0.4*_BALL_RADIUS)
{
  radius=rad;
  setToolTip(QString("BALL"));
  QCursor cur = Qt::OpenHandCursor; 
  setCursor(cur);
  setAcceptedMouseButtons(Qt::LeftButton);
  QPainter painter(&pixmap);
  painter.scale(0.2,0.2);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(_BALL_RADIUS,_BALL_RADIUS);
  paint(&painter, 0, 0);
  painter.end();
}

QRectF Gball::boundingRect() const
{
  return QRectF(QPointF(-radius,-radius),QPointF(radius,radius));
}

void Gball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(QBrush(QColor(255,120,0,255)));
  painter->drawEllipse(QRectF(QPointF(-radius,-radius),QPointF(radius,radius)));
}
void Gball::mousePressEvent(QGraphicsSceneMouseEvent *evt)
 {
     setCursor(Qt::ClosedHandCursor);
 }
void Gball::mouseReleaseEvent(QGraphicsSceneMouseEvent *evt)
 {
     setCursor(Qt::OpenHandCursor);
 }
void Gball::mouseMoveEvent(QGraphicsSceneMouseEvent *evt)
{
    QDrag *drag = new QDrag(evt->widget());
    QMimeData *mime =  new QMimeData;
    drag->setMimeData(mime);
    mime->setText(QString("BALL"));
    setCursor(Qt::OpenHandCursor);
    drag->setPixmap(pixmap);
    drag->exec();
}


//----------------------------------
//----------------------------------

GCanvas::GCanvas(int R,int G,int B)
{
  r=R;
  b=B;
  g=G;
  scount=0;
  mypath=NULL;
  numEle=0;
}

QRectF GCanvas::boundingRect() const
{
  return QRectF(-boundary_width,-boundary_width,field_length+2*boundary_width,field_width+2*boundary_width);
}

int GCanvas::addCircle(int x,int y,int radius)
{
  items[numEle].type = ElementType::CIRCLE;
  items[numEle].element.circle.x = x;
  items[numEle].element.circle.y = y;
  items[numEle].element.circle.radius = radius;
  numEle++;
  return (numEle-1);
}

int GCanvas::addLine(int x1,int y1,int x2,int y2)
{
  items[numEle].type=ElementType::LINE;
  items[numEle].element.line.x1=x1;
  items[numEle].element.line.x2=x2;
  items[numEle].element.line.y1=y1;
  items[numEle].element.line.y2=y2;
  numEle++;
  return (numEle-1);
}
/*
int GCanvas::contLineTo(int x,int y)
{
  typeEle[numEle]='l';
  d1[numEle]=x;
  e1[numEle]=y;
  numEle++;
  update();
  return (numEle-1);
}

int GCanvas::addEllipse(int x,int y,int a,int b)
{
  typeEle[numEle]='E';
  d1[numEle]=x;
  e1[numEle]=y;
  d2[numEle]=a;
  e2[numEle]=b;
  numEle++;
  update();
  return (numEle-1);
}

int GCanvas::contCubicTo(int x1,int y1,int x2,int y2,int x3,int y3)
{
  typeEle[numEle]='c';
  d1[numEle]=x1;
  e1[numEle]=y1;
  d2[numEle]=x2;
  e2[numEle]=y2;
  d3[numEle]=x3;
  e3[numEle]=y3;
  numEle++;
  update();
  return (numEle-1);
}

int GCanvas::contQuadTo(int x1,int y1,int x2,int y2)
{
  typeEle[numEle]='q';
  d1[numEle]=x1;
  e1[numEle]=y1;
  d2[numEle]=x2;
  e2[numEle]=y2;
  update();
  return (numEle-1);
}
*/
int GCanvas::addText(int x,int y,char* str)
{
  items[numEle].type = ElementType::TEXT;
  strcpy(items[numEle].element.text.str, str);
  items[numEle].element.text.x = x;
  items[numEle].element.text.y = y;
  return (numEle-1);
}
/*
bool GCanvas::removeItem(int item_No)
{
  if(item_No>=numEle||item_No<0)
  return false;
  //TODO:Develop a better way to do update and remove items.
  typeEle[item_No]='X';
  update();
  return true;
}
*/
void GCanvas::clear()
{
  if (mypath)
  {
  delete(mypath);
  }
  mypath=NULL;
  numEle=0;
  curCount=0;
}
/*
bool GCanvas::updateItem(int i,int _d1,int _e1,int _d2,int _e2,int _d3,int _e3)
{
  d1[i]=_d1;
  e1[i]=_e1;
  if(typeEle[i]!='T')
  d2[i]=_d2;
  e2[i]=_e2;
  d3[i]=_d3;
  e3[i]=_e3;
  curCount=0;
  delete(mypath);
  mypath=NULL;
  update();
  return true;
}
*/

int GCanvas::addEle(CanvasItem item)
{
  if (item.type==ElementType::CIRCLE ) 
  {
  return this->addCircle(item.element.circle.x,item.element.circle.y,item.element.circle.radius);
  } 
  else if (item.type==ElementType::LINE ) 
  {
  return this->addLine(item.element.line.x1,item.element.line.y1,item.element.line.x2,item.element.line.y2);
  }
  else if (item.type==ElementType::TEXT ) 
  {
  return this->addText(item.element.text.x, item.element.text.y, item.element.text.str);
  }
  return -1;
}

void GCanvas::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(QColor(r,g,b,255));
  if(!mypath)
  {
  mypath=new QPainterPath();
  curCount=0;
  mypath->addEllipse(QRectF(-1,-1,2,2));
  }
  Circle c;
  Line   l;
  Text   t;
  for(int i=curCount;i<numEle;++i)
  {
  switch(items[i].type)
  {
  case ElementType::CIRCLE:
    c=items[i].element.circle;
    mypath->addEllipse(QRectF(QPointF(c.x-c.radius,c.y-c.radius),QPointF(c.x+c.radius,c.y+c.radius)));
    break;
  case ElementType::LINE:
    l=items[i].element.line;
    mypath->moveTo(QPointF(l.x1,-l.y1));
    mypath->lineTo(l.x2,-l.y2);
    break;
  case ElementType::TEXT:
    t=items[i].element.text;
    mypath->addText(QPointF(t.x,t.y),QFont(QString("Cronyx-Helvetica"),10,10,false),  QString(t.str));
    break;
  }
  }
  painter->drawPath(*mypath);
}
GCanvas::~GCanvas()
{
  delete(mypath);
}
