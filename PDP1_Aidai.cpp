#include <stdio.h>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <math.h>


using namespace std;

int numberThreads = 8;
int iterrationNum = 1000000;

float q, p, b, i, j, k  = 0;

float t = 0.01;

float varX = 0.4;
float varY = 0.1;
float varZ = 0.8;

/******************************************************************************/

float floatRand ( float low, float high )
{
    return ( (float)rand() * ( high - low ) ) / (float)RAND_MAX + low;
}

int runIt(int tid, float q, float p, float b){

  varX = floatRand(0.1, 1.0);
  varY = floatRand(0.1, 1.0);
  varZ = floatRand(0.1, 1.0);

  for(int iter = 0; iter < iterrationNum; ++iter){
    
  

     float x = t * ((varZ * varY) / q);
     float y = t * (varY - varX + p);
     float z = t * (b + varY);


    
    varX += x;
    varY += y;
    varZ += z;
    printf("%f, %f, %f\n", q, p, b);
    printf("tid: %d, running iter %d!, valX=%f, valY=%f, valZ=%f \n", tid, iter, varX, varY, varZ);
  }

  return 0;
}

/******************************************************************************/
int main(int argc, char* argv[]){

  unsigned concurentThreadsSupported = std::thread::hardware_concurrency();
  numberThreads = concurentThreadsSupported;
  printf("The number of cores: %d\n", numberThreads);

  int MULTITHREAD = 1; 
  if(argc == 2){
    MULTITHREAD = atof(argv[1]);
  }

  time_t theStart, theEnd;
  time(&theStart);


  if(MULTITHREAD){
    thread zThreads[numberThreads];

    for (float i = 0.05; i < 1; i+=0.05){
      for (float j = 0.05; j < 1; j+=0.05){
        for (float k = 0.05; k < 1; k+=0.05){
              for(int tid=0; tid < numberThreads-1; tid++){
                zThreads[tid] = thread(runIt, tid, i, j, k);
              }

              runIt(numberThreads-1, i, j, k);
              for(int tid=0; tid<numberThreads-1; tid++){
                zThreads[tid].join();
              }
        }
      }
    }

}
  else{
      for(int tid=0; tid<8; tid++){
        runIt(tid, i, j, k);
        }
  }

  time(&theEnd);
  if(MULTITHREAD)
    printf("MULTITHREADING seconds used: %ld\n", theEnd - theStart);
  else
    printf("NOT THREADING seconds used: %ld\n", theEnd - theStart);
  return 0;
}

/******************************************************************************/
