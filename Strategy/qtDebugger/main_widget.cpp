#include "main_widget.h"
#include <QtGui/QtGui>
#include <QtGui/QPaintEvent>
#include <QtGui/QBrush>
#include <QtGui/QPen>
#include <QtGui/QPixmap>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>
#include "render_area.h"
#include "../fieldConfig.h"
#include <iostream>
using namespace std;
MainWidget::MainWidget(Strategy::BeliefState &state_, QWidget *parent) :
  QWidget(parent),
  state(state_)
{
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(32);
}
MainWidget::~MainWidget()
{
}
void MainWidget::setName(const QString &name)
{
}
QString MainWidget::name() const
{
  return "Jai Gupta";
}
int tr_x(int x, float fac) {
  return (HALF_FIELD_MAXX+x)*fac;
}
int tr_y(int y, float fac) {
  return (HALF_FIELD_MAXY-y)*fac;
}
void MainWidget::paintEvent(QPaintEvent* event)
{
  int my_w = width();
  int my_h = height();
  float fac_w = my_w / (float)HALF_FIELD_MAXX;
  float fac_h = my_h / (float)HALF_FIELD_MAXY;
  float fac = (fac_w < fac_h) ? fac_w : fac_h;
  fac /= 2;
  
  QPainter painter(this);
  painter.setPen(pen);
  painter.setBrush(brush);
  if (antialiased)
    painter.setRenderHint(QPainter::Antialiasing, true);
  QRect rect(-BOT_RADIUS * fac, -BOT_RADIUS * fac, 2*BOT_RADIUS * fac, 2*BOT_RADIUS * fac);
  painter.save();
  painter.fillRect(0, 0, (2*HALF_FIELD_MAXX)*fac, (2*HALF_FIELD_MAXY)*fac, Qt::green);
  painter.restore();
  QColor orange(255,128,128);
  pen.setColor(orange);
  painter.setPen(pen);
  painter.save();
  painter.drawEllipse(tr_x(state.ballPos.x-BALL_RADIUS, fac), tr_y(state.ballPos.y-BALL_RADIUS, fac), 2*BALL_RADIUS*fac, 2*BALL_RADIUS*fac);
  painter.restore();
  QColor blue(0,0,255);
  pen.setColor(blue);
  painter.setPen(pen);
  for(int i = 0; i < BOT_COUNT; i++)
  {
    //cout<<i<<" "<<state.homePos[i].x<< " "<<state.homePos[i].y<<endl;
    painter.save();
    painter.translate((HALF_FIELD_MAXX + state.homePos[i].x)*fac, (HALF_FIELD_MAXY - state.homePos[i].y)*fac);
    painter.drawEllipse(rect);
    painter.restore();
    painter.save();
    QPoint midp((HALF_FIELD_MAXX + state.homePos[i].x)*fac, (HALF_FIELD_MAXY - state.homePos[i].y)*fac);
    QPoint endp((HALF_FIELD_MAXX + state.homePos[i].x + BOT_RADIUS*cos(state.homeAngle[i]))*fac,
                (HALF_FIELD_MAXY - state.homePos[i].y - BOT_RADIUS*sin(state.homeAngle[i]))*fac);
    painter.drawLine(midp, endp); //draw Direction
    painter.restore();
  }
  QColor yellow(255,0,0);
  pen.setColor(yellow);
  painter.setPen(pen);
  for(int i = 0; i < BOT_COUNT; i++)
  {
    painter.save();
    painter.translate((HALF_FIELD_MAXX + state.awayPos[i].x)*fac, (HALF_FIELD_MAXY - state.awayPos[i].y)*fac);
    painter.drawEllipse(rect);
    painter.restore();
    painter.save();
    QPoint midp((HALF_FIELD_MAXX + state.awayPos[i].x)*fac, (HALF_FIELD_MAXY - state.awayPos[i].y)*fac);
    QPoint endp((HALF_FIELD_MAXX + state.awayPos[i].x + BOT_RADIUS * cos(state.awayAngle[i]))*fac,
                (HALF_FIELD_MAXY - state.awayPos[i].y - BOT_RADIUS * sin(state.awayAngle[i]))*fac);
    painter.drawLine(midp, endp); //draw Direction
    painter.restore();
  }
  painter.setRenderHint(QPainter::Antialiasing, false);
  painter.setPen(palette().dark().color());
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
  timer->start(32);
}
