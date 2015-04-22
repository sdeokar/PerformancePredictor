#include "stdafx.h"
#include <iostream>
#include "TrainingExample.h"

using namespace std;

TrainingExample::TrainingExample(void)
{
    this->index = 0;
    this->distance = 0;
    for(U32 i = 0; i < NO_OF_ATT; i++)
        this->value[i] = 0.0;
}

TrainingExample::~TrainingExample(void)
{
    this->index = 0;
    this->distance = 0;
    for(U32 i = 0; i < NO_OF_ATT; i++)
        this->value[i] = 0.0;
}

U32 TrainingExample::GetIndex(void)
{
    return this->index;
}

void TrainingExample::SetIndex(U32 index)
{
    this->index = index;
}

void TrainingExample::SetVal(double *a)
{
    if(a)
    {
        for(U32 i = 0; i < NO_OF_ATT; i++)
            this->value[i] = a[i];
    }
}

void TrainingExample::GetVal(double *a)
{
    if(a)
    {
        for(U32 i = 0; i < NO_OF_ATT; i++)
            a[i] = this->value[i];
    }
}

double TrainingExample::GetDistance(void)
{
    return this->distance;
}

void TrainingExample::SetDistance(double distance)
{
    this->distance = distance;
}

void TrainingExample::CalculateDistance(void)
{
}