#ifndef STACK_H
#define STACK_H
#include "Point.h"
#define MAX_STACK_SIZE 10000

namespace KGPVisionGUI
{
  class Stack
  {
  public:
    Stack();
    ~Stack();
    void push(Point2D pt);
    Point2D pop();
    bool isEmpty();
    bool isFull();
    void resetStack();
  private:
    int top;
    Point2D blobstack[MAX_STACK_SIZE];
  };
}

#endif //STACK