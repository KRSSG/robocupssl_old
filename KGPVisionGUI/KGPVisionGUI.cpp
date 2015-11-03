// KGPVisionGUI.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include <time.h>

using namespace KGPVisionGUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false); 

  // Create the main window and run it
  Application::Run(gcnew Form1());
/*
  if(cap)
  {
    cvReleaseImage(&HSVframe);
    cvReleaseImage(&BinImage);
    cvReleaseCapture(&cap);
  } */
  return 0;
}
