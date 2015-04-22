// PerformancePredictor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include "TrainingExample.h"

using namespace std;

typedef list<TrainingExample, 
			allocator<TrainingExample> > TRAINING_EXAMPLES_LIST;

void NormalizeByStandardDeviation (TRAINING_EXAMPLES_LIST *trainList, 
								   U32 trainExamples)
{
	for(U32 i = 0; i < NO_OF_ATT -1; i++)
	{
		/* Find the mean */
		double mean = 0.0;
		TRAINING_EXAMPLES_LIST::iterator Iter;
		TrainingExample tmpTestObj;
		for(Iter = trainList->begin(); Iter != trainList->end(); ++Iter)
		{
			tmpTestObj = *Iter;
			mean += tmpTestObj.value[i];
		}
		mean = (mean / (double)trainExamples);

		/* Find the deviation */
		double deviation = 0.0;
		for(Iter = trainList->begin(); Iter != trainList->end(); ++Iter)
		{
			tmpTestObj = *Iter;
			double val = mean - tmpTestObj.value[i];
			deviation += val*val;
		}
		deviation = (deviation / (double)trainExamples);
		deviation = sqrt (deviation);

		/* Normalize the values */
		for(Iter = trainList->begin(); Iter != trainList->end(); ++Iter)
		{
			tmpTestObj = *Iter;
			double val = (tmpTestObj.value[i] - mean)/deviation;
			Iter._Ptr->_Myval.value[i] = val;
		}
	}
}

size_t GetLine (char *line, U32 max, FILE *fp)
{
   if(fgets(line, max, fp)==NULL)
      return 0;
   else
      return strlen(line);
}

void ParseData(char *filename, TRAINING_EXAMPLES_LIST *rlist, U32 *rlistExamples)
{
    if(filename && rlist && rlistExamples)
    {
        FILE *fp = NULL;
        U32 len = 0;
        char line[LINE_MAX+1];
        U32 lineSize = LINE_MAX;
        TrainingExample *TEObj;
        U32 index = 0;
        U32 numExamples = 0;

        *rlistExamples = 0;

        line[0] = 0;

        if((fp = fopen (filename, "r")) == NULL)
        {
            cout<<"Error in opening file."<<endl;
            return;
        }

        //Initialize weights to random values
        srand (time(NULL));

        char *tmp;
        int tmpParams = 0; //NO_OF_ATT;
        int i = 0;
        double cd = 0.0;

        /* Read the data file line by line */
        while((len = GetLine (line, lineSize, fp))!=0) 
        {
            TEObj = new TrainingExample ();
            tmp = strtok (line,",");
            while (tmp != NULL)
            {
                cd = atof (tmp);
                TEObj->value[tmpParams] = cd;
                tmpParams ++;

                tmp = strtok (NULL, ",");

                if(tmpParams == NO_OF_ATT)
                {
                    tmpParams = 0;
                    cd = 0.0;
                    line[0] = 0;
                    numExamples ++;
  
                    TEObj->index = index++;
                    break;
                }
            }

            rlist->insert (rlist->end(), *TEObj);

            delete TEObj;
        }

        *rlistExamples = numExamples;
    }
}

int main(S32 argc, char *argv[])
{
    TRAINING_EXAMPLES_LIST trainingList;
    U32 trainingListSize = 0;
    TRAINING_EXAMPLES_LIST testingList;
    U32 testingListSize = 0;
 
    ParseData("Train.txt", &trainingList, &trainingListSize);
    ParseData("Test.txt", &testingList, &testingListSize);


	return 0;
}

