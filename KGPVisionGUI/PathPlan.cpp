#include <stdio.h>
#include <time.h>
#include <math.h>
#include "PathPlan.h"
#define _CRT_SECURE_NO_WARNINGS
#define DEG_TO_RAD (0.0174533)
#define RAD_TO_DEG (57.2958)

int CurrIndex = 0,ProcessIndex = 0;
Node *nodes;
Point *NewWay,*BiasedWay;

bool Connect(Point Start,Point End,Obstacle obs[],int nObs)
{
  float A,B,C,D,dot,len_sq,param,xx,yy;
  int i;
  for(i = 0; i < nObs;i++)
  {
    A = obs[i].x - Start.x; // vector from one point to test point
    B = obs[i].y - Start.y;
    C = End.x - Start.x; //vector from one endpoint to the other end point
    D = End.y - Start.y;

    dot = A * C + B * D;
    len_sq = C * C + D * D;
    param = dot / len_sq; // length range reduced to (0,1)
    
    if(param < 0)
    {
      xx = Start.x;
      yy = Start.y;
    }
    else if(param > 1)
    {
      xx = End.x;
      yy = End.y;
    }
    else 
    {
      xx = Start.x + param*C;
      yy = Start.y + param*D;
    }

    if((obs[i].x - xx)*(obs[i].x - xx) + (obs[i].y - yy)*(obs[i].y - yy) < obs[i].radius*obs[i].radius)
    {
      return false;
    }
  }
  return true;
}

int NextNode(Point Start,Point End,Obstacle obs[],int nObs)
{
  int i = 0,j = 0,count = 0;
  bool nodeFound = false;
  Point searchTemp,node[20];
  float theta[20],temp;
  float LocalTheta,SearchTheta,radius;
  LocalTheta = atan2(End.y - Start.y,End.x - Start.x)*(RAD_TO_DEG);
  SearchTheta = LocalTheta - 45;

  searchTemp.x = obs[0].x;
  searchTemp.y = obs[0].y;
  radius = (searchTemp.x - Start.x)*(searchTemp.x - Start.x) + (searchTemp.y - Start.y)*(searchTemp.y - Start.y);
  for(i = 0;i < nObs;i++)
  {
    if(radius > (obs[i].x - Start.x)*(obs[i].x - Start.x) + (obs[i].y - Start.y)*(obs[i].y - Start.y))
    {
      searchTemp.x = obs[i].x;
      searchTemp.y = obs[i].y;
      radius = (searchTemp.x - Start.x)*(searchTemp.x - Start.x) + (searchTemp.y - Start.y)*(searchTemp.y - Start.y);
    }
  }
  radius = 0.8* sqrt(radius);

  for(i = 0;i < 20; i++)
  {
    theta[i] = SearchTheta + (rand()%9000)/100.0f;
    node[i].x = Start.x + radius*cos(theta[i]*(DEG_TO_RAD));
    node[i].y = Start.y + radius*sin(theta[i]*(DEG_TO_RAD));
    if(Connect(Start,node[i],obs,nObs))
    {
      nodeFound = true;
      nodes[++CurrIndex].point = node[i];
      nodes[CurrIndex].ParentIndex = ProcessIndex;
      nodes[CurrIndex].Length += radius + nodes[ProcessIndex].Length;
      if(Connect(nodes[CurrIndex].point,End,obs,nObs))
        return CurrIndex;
    }
  }

  if(!nodeFound)
  {
    for(i = 0;i < 20; i++)
    {
      temp = (rand()%18000)/100.0f;
      if(temp > 90)
        theta[i] = SearchTheta + temp;
      else
        theta[i] = SearchTheta - temp;
      node[i].x = Start.x + radius*cos(theta[i]*(DEG_TO_RAD));
      node[i].y = Start.y + radius*sin(theta[i]*(DEG_TO_RAD));
      if(Connect(Start,node[i],obs,nObs))
      {
        nodeFound = true;
        nodes[++CurrIndex].point = node[i];
        nodes[CurrIndex].ParentIndex = ProcessIndex;
        nodes[CurrIndex].Length += radius + nodes[ProcessIndex].Length;
        if(Connect(nodes[CurrIndex].point,End,obs,nObs))
          return CurrIndex;
      }
      
    }
  }

  if(!nodeFound)
  {
    for(i = 0;i < 20; i++)
    {
      theta[i] = (SearchTheta + (rand()%9000)/100.0f)*(-1);
      node[i].x = Start.x + radius*cos(theta[i]*(DEG_TO_RAD));
      node[i].y = Start.y + radius*sin(theta[i]*(DEG_TO_RAD));
      if(Connect(Start,node[i],obs,nObs))
      {
        nodeFound = true;
        nodes[++CurrIndex].point = node[i];
        nodes[CurrIndex].ParentIndex = ProcessIndex;
        nodes[CurrIndex].Length += radius + nodes[ProcessIndex].Length;
        if(Connect(nodes[CurrIndex].point,End,obs,nObs))
          return CurrIndex;
      }
      
    }
  }

//  if(!nodeFound)
//    printf("No path found\n");
  return -1;
}

void PathPlan(Point Start,Point End,Point LastWay[],int nLastWayPts,Obstacle obs[],int nObs,Point PathWay[])
{
    ProcessIndex = CurrIndex = 0;
    if(!nodes)
        nodes = (Node *)calloc(10000,sizeof(Node));
    else
        memset(nodes,0,sizeof(Node)*10000);

    if(!BiasedWay)
        BiasedWay = (Point *)calloc(100,sizeof(Point));
    else
        memset(BiasedWay,0,sizeof(Point)*100);

    if(!NewWay)
        NewWay = (Point *)calloc(100,sizeof(Point));
    else
        memset(NewWay,0,sizeof(Point)*100);

  float NewPathLength = 0,LastPathLength = 0,checkTheta = 0,checkRadius = 0;
  int saveIndex = -1,i,nBiasedWay =0,count = 0,nNewWay = 0;
  srand(time(NULL));
  Point NewWay[100],BiasedWay[100];
    
    for(i = 0;i < nObs ;i++)
    {
        if((checkRadius = (End.x - obs[i].x)*(End.x - obs[i].x) + (End.y - obs[i].y)*(End.y - obs[i].y)) < obs[i].radius*obs[i].radius)
        {
            checkTheta = rand()%90;
            checkRadius = sqrt(checkRadius) + 40;
            if(End.x >= obs[i].x) End.x = (obs[i].x + checkRadius*cos(checkTheta*(DEG_TO_RAD)) >= 700) ? obs[i].x - checkRadius*cos(checkTheta*(DEG_TO_RAD)) : obs[i].x + checkRadius*cos(checkTheta*(DEG_TO_RAD)); 
            if(End.y >= obs[i].y) End.y = (obs[i].y + checkRadius*sin(checkTheta*(DEG_TO_RAD)) >= 500) ? obs[i].y - checkRadius*sin(checkTheta*(DEG_TO_RAD)) : obs[i].y + checkRadius*sin(checkTheta*(DEG_TO_RAD)); 
        }
        if((Start.x - obs[i].x)*(Start.x - obs[i].x) + (Start.y - obs[i].y)*(Start.y - obs[i].y) < obs[i].radius * obs[i].radius)
            obs[i].radius = 0.66*obs[i].radius;
    }
  for(i = 0; i < nLastWayPts; i++)
  {
    if((Start.x - LastWay[i].x)*(Start.x - LastWay[i].x) + (Start.y - LastWay[i].y)*(Start.y - LastWay[i].y) < DISTANCE_THRESHOLD_2)
    {
      saveIndex = i;
            break;
    }
  }

  nodes[0].Length = 0;
  nodes[0].point = Start;
  nodes[0].ParentIndex = -1;

    if(nLastWayPts > 0)
        LastPathLength += sqrt((Start.x-LastWay[0].x)*(Start.x-LastWay[0].x)+(Start.y-LastWay[0].y)*(Start.y-LastWay[0].y));
    for(i = 0; i < nLastWayPts-1; i++)
    {
        LastPathLength += sqrt((LastWay[i].x-LastWay[i+1].x)*(LastWay[i].x-LastWay[i+1].x)+(LastWay[i].y-LastWay[i+1].y)*(LastWay[i].y-LastWay[i+1].y));
    }

    if(nLastWayPts > 0)
    {
      if(saveIndex == -1)
        {
        if(Connect(Start,LastWay[0],obs,nObs))
            {
          nodes[++CurrIndex].point = LastWay[0];
          nodes[CurrIndex].ParentIndex = ProcessIndex;
          nodes[CurrIndex].Length += nodes[ProcessIndex].Length + sqrt((nodes[ProcessIndex].point.x - LastWay[0].x)*(nodes[ProcessIndex].point.x - LastWay[0].x) + (nodes[ProcessIndex].point.y - LastWay[0].y)*(nodes[ProcessIndex].point.y - LastWay[0].y));
          ProcessIndex++;
            }
          
        for(i = 0; i < nLastWayPts-1; i++)
        {
          if(Connect(LastWay[i],LastWay[i+1],obs,nObs))
          {
            nodes[++CurrIndex].point = LastWay[i+1];
            nodes[CurrIndex].ParentIndex = ProcessIndex;
            nodes[CurrIndex].Length += nodes[ProcessIndex].Length + sqrt((nodes[ProcessIndex].point.x - nodes[CurrIndex].point.x)*(nodes[ProcessIndex].point.x - nodes[CurrIndex].point.x) + (nodes[ProcessIndex].point.y - nodes[CurrIndex].point.y)*(nodes[ProcessIndex].point.y - nodes[CurrIndex].point.y));
            ProcessIndex++;
          }
          else
            break;
        }

        while(CurrIndex < 10000 && !Connect(nodes[ProcessIndex].point,End,obs,nObs) && ProcessIndex <= CurrIndex)
        {
          if(NextNode(nodes[ProcessIndex].point,End,obs,nObs) == -1)
          {
            ProcessIndex++;
          }
          else
            break;
        }
        nBiasedWay = 0;
        BiasedWay[nBiasedWay] = nodes[CurrIndex].point;
        LastPathLength = nodes[CurrIndex].Length + sqrt((nodes[CurrIndex].point.x-End.x)*(nodes[CurrIndex].point.x-End.x) + (nodes[CurrIndex].point.y-End.y)*(nodes[CurrIndex].point.y-End.y));
        nBiasedWay++;
        i = nodes[CurrIndex].ParentIndex;
        while(i != -1)
        {
          BiasedWay[nBiasedWay++] = nodes[i].point;
          i = nodes[i].ParentIndex;
        }
        }
        else
      {
        i = saveIndex;
        LastWay[i] = Start;
        for(i = saveIndex; i < nLastWayPts-1; i++)
        {
          if(Connect(LastWay[i],LastWay[i+1],obs,nObs))
          {
            nodes[++CurrIndex].point = LastWay[i+1];
            nodes[CurrIndex].ParentIndex = ProcessIndex;
            nodes[CurrIndex].Length += nodes[ProcessIndex].Length + sqrt((nodes[ProcessIndex].point.x - nodes[CurrIndex].point.x)*(nodes[ProcessIndex].point.x - nodes[CurrIndex].point.x) + (nodes[ProcessIndex].point.y - nodes[CurrIndex].point.y)*(nodes[ProcessIndex].point.y - nodes[CurrIndex].point.y));
            ProcessIndex++;
          }
          else
            break;
        }

        while(CurrIndex < 10000 && !Connect(nodes[ProcessIndex].point,End,obs,nObs) && ProcessIndex <= CurrIndex)
        {
          if(NextNode(nodes[ProcessIndex].point,End,obs,nObs) == -1)
          {
            ProcessIndex++;
          }
          else
            break;
        }
        nBiasedWay = 0;
        BiasedWay[nBiasedWay] = nodes[CurrIndex].point;
        LastPathLength = nodes[CurrIndex].Length + sqrt((nodes[CurrIndex].point.x-End.x)*(nodes[CurrIndex].point.x-End.x) + (nodes[CurrIndex].point.y-End.y)*(nodes[CurrIndex].point.y-End.y));
        nBiasedWay++;
        i = nodes[CurrIndex].ParentIndex;
        while(i != -1)
        {
          BiasedWay[nBiasedWay++] = nodes[i].point;
          i = nodes[i].ParentIndex;
        }
      }
    }
    
    memset(nodes,0,sizeof(Node)*10000);
  ProcessIndex = CurrIndex = 0;
  nodes[0].Length = 0;
  nodes[0].ParentIndex = -1;
  nodes[0].point = Start;

  while(CurrIndex < 10000 && !Connect(nodes[ProcessIndex].point,End,obs,nObs) && ProcessIndex <= CurrIndex)
  {
    if(NextNode(nodes[ProcessIndex].point,End,obs,nObs) == -1)
    {
        ProcessIndex++;
    }
    else
      break;
  }

  nNewWay = 0;
  NewWay[nNewWay] = nodes[CurrIndex].point;
  NewPathLength = nodes[CurrIndex].Length + sqrt((nodes[CurrIndex].point.x-End.x)*(nodes[CurrIndex].point.x-End.x) + (nodes[CurrIndex].point.y-End.y)*(nodes[CurrIndex].point.y-End.y));
  nNewWay++;
  i = nodes[CurrIndex].ParentIndex;
  while(i != -1)
  {
    NewWay[nNewWay++] = nodes[i].point;
    i = nodes[i].ParentIndex;
  }

  if(nLastWayPts == 0 || NewPathLength <= HYSTERESIS_PATH_GEN*LastPathLength)
  {
    for(i = 1;i < nNewWay;i++)
    {
      PathWay[i-1] = NewWay[nNewWay - i-1];
    }
  }
  else
  {
    for(i = 1;i < nBiasedWay;i++)
    {
        PathWay[i-1] = BiasedWay[nBiasedWay - i-1];
//           PathWay[i] = LastWay[i];
    }
  }
  PathWay[i-1] = End;

}
