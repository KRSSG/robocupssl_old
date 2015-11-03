#include "thread.h"
#include <QtGui/QApplication>
#include "../beliefState.h"
class QtDebugger
{
public:
  QtDebugger(QApplication *app, Strategy::BeliefState &state);
  ~QtDebugger();
  QApplication* a;
  Strategy::BeliefState &state;
  void run();
};