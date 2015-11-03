#include "stdafx.h"
#include "Vision.h"
#include <fstream> 
using namespace std;

namespace KGPVisionGUI 
{
  Vision::Vision()
  {
    for(int i = 0;i<MAX_COLORS;i++)
    {
      Parameters[i].maxhsv.h = Parameters[i].maxhsv.s = Parameters[i].maxhsv.v = 0;
      Parameters[i].minhsv.h = Parameters[i].minhsv.s = Parameters[i].minhsv.v = 0;
      Parameters[i].blobMaxDist = Parameters[i].blobMinDist = 0;
    }
  }
  Vision::~Vision()
  {}
  void Vision::saveColorParameters()
  {
     ofstream File("ColorParameters.txt");
     for(int i = 0;i<MAX_COLORS;i++)
     {
      File << Parameters[i].maxhsv.h<<" "<<Parameters[i].minhsv.h
          <<" "<< Parameters[i].maxhsv.s<<" "<<Parameters[i].minhsv.s
          <<" "<< Parameters[i].maxhsv.v<<" "<<Parameters[i].minhsv.v
          <<" "<< Parameters[i].blobMaxDist <<" "<<Parameters[i].blobMinDist<<"\n";
     }
     File.close();
  }
  void Vision::loadColorParameters()
  {
    ifstream File("ColorParameters.txt");
    for(int i = 0;i<MAX_COLORS;i++)
    {
      File >> Parameters[i].maxhsv.h >> Parameters[i].minhsv.h
           >> Parameters[i].maxhsv.s >> Parameters[i].minhsv.s
           >> Parameters[i].maxhsv.v >> Parameters[i].minhsv.v
           >> Parameters[i].blobMaxDist >> Parameters[i].blobMinDist;
    }
    File.close();
  }
  void Vision::saveBotParameters()
  {
     ofstream File("BotParameters.txt");
      File << markerSize<<"\n";
     File.close();
  }
  void Vision::loadBotParameters()
  {
    ifstream File("BotParameters.txt");
      File >> markerSize;
    File.close();
  }
}
