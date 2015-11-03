#ifndef _PATHPLAN_
#define _PATHPLAN_

#include <stdlib.h>
#include <string.h>
#include "Definitions.h"

#define HYSTERESIS_PATH_GEN 0.95

bool Connect(Point Start,Point End,Obstacle obs[],int nObs);
int NextNode(Point Start,Point End,Obstacle obs[],int nObs);
void PathPlan(Point Start,Point End,Point *LastWay,int nLastWayPts,Obstacle obs[],int nObs,Point PathWay[]);

#endif 