#ifndef __TRAINING_EXAMPLE_H
#define __TRAINING_EXAMPLE_H

#include "stdafx.h"
#include <list>
#include <string>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <time.h>

#define U32 unsigned int
#define S32 int
#define NO_OF_ATT 10
#define LINE_MAX 10000

using namespace std;

class TrainingExample
{
public:
    U32 index;
    double value[NO_OF_ATT];
    double distance;

    TrainingExample(void);
    ~TrainingExample(void);
    void SetIndex(U32 val);
    U32 GetIndex(void);
    void SetVal(double *a);
    void GetVal(double *a);
    void SetDistance(double val);
    double GetDistance(void);
    void CalculateDistance(void);
};
#endif