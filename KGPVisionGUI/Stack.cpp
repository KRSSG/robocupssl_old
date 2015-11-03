#include "stdafx.h"
#include "Stack.h"
namespace KGPVisionGUI
{
Stack::Stack()
  {
    top = 0;
  }

  Stack::~Stack()
  {}

  void Stack::push(Point2D blobpixel)
  {
    blobstack[top++] = blobpixel;
  }

  Point2D Stack::pop()
  {
    top--;
    return blobstack[top];
  }

  bool Stack::isEmpty()
  {
    return (top == 0);
  }

  bool Stack::isFull()
  {
    return (top >= MAX_STACK_SIZE);
  }

  void Stack::resetStack()
  {
    top = 0;
  }
}
