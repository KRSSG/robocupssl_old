#ifndef INCL_GRAPHICSITEM_H
#define INCL_GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <string>
#include "config.h"
#include "rbCommDef.h"
#include "entityInfo.h"
#include "RbCentral.h"

// Class Graphical Bots
namespace Simulator
{
  class Gbot : public QGraphicsItem
  {
  private:
    int BOT_RADIUS;
    int teamNo;
    int botID;
    float x,y;
    QPixmap pixmap;
    PhysxEngine::PosInfo *posInfo;
  
  public:
    Gbot(PhysxEngine::PosInfo &posInfo, int botID, int team=YELLOW,int radius=_BOT_RADIUS);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    ~Gbot();
    
    QRectF boundingRect() const;
    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
  }; // class Gbot


  class Gfield : public QGraphicsObject
  {
  public:
    QPointF startPoint;
    Gfield(Simulator::RbCentral &rbCen);
    PhysxEngine::PosInfo *posInfo;
    Simulator::RbCentral *rbCen;
    QRectF boundingRect() const;     
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
  }; // cLass Gfield


  //class Graphical Ball
  class Gball:public QGraphicsItem
  {
  private:
    int radius;
  
  public:
    Gball(int radius);
    QPixmap pixmap;

    QRectF boundingRect()const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
  }; // class Gball
  
  //Graphical Canvas for on the go Drawing of objects
  class GCanvas:public QGraphicsItem
  {
  private:
    //------------Variables to store drawing on the way------------------
    int numEle;   //Stores the number of graphics items to draw
    int r,b,g;
    int curCount;
    int scount;
    HAL::CanvasItem items[MAX_ITEMS];
    QPainterPath *mypath;
    
  public:
    GCanvas(int r,int g,int b);
  
    ~GCanvas();
    
    QRectF boundingRect() const;
    
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    
    int addCircle(int x,int y,int radius);
    
    int addLine(int x1,int y1,int x2,int y2);
    
    // int contLineTo(int x,int y);
    
    // int addEllipse(int centerX,int centerY,int a,int b);
    
    int addText(int x,int y,char *str);
    
    int addEle(HAL::CanvasItem item);
    
    // int contCubicTo(int x1,int y1,int x2,int y2,int x3,int y3);
    
    // int contQuadTo(int x1,int y1,int x2,int y2);
    
    // bool removeItem(int itemNo=0);
    
    void clear();
    
    bool updateItem(int ItemNo,int d1=0,int e1=0,int d2=0,int e2=0,int d3=0,int e3=0);
  };
} // namespace Simulator

#endif // INCL_GRAPHICSITEM_H
