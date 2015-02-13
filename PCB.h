#ifndef _PCB_h
#define _PCB_h
#include <stdio.h>
#include <stdlib.h>

struct PCB
{
int processID;
long arrivalTimeStamp;
long totalBurstTime;
long executionStartTime;
long executionEndTime;
long remainingBurstTime;
int processPriority;
};

typedef struct PCB PCB;

#endif