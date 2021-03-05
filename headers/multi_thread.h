#include <pthread.h>
using namespace std;
//int bs = 16;

int *A,*B;               //Global variables for matA and matB
int *output;
int N;                   //Global variable for N
int num_threads =64;     //Number of threads in the program

struct struct_thrd{      //sturcture for every thread having thread number and an array
    int threadno;        //thread number
    int* arr;            // array having part of output which is computed by a particular thread
};


void* mul(void* arg){

    struct struct_thrd *args = (struct struct_thrd*) arg;
    (args->arr) = (int*)malloc((2*N-1)*sizeof(int));
    
    for(int i = 0 ; i < N;i += 16)    // 16 is for blocksize
    {
     for(int j = 0; j < N;j +=16)
      {
      if((i+j)%num_threads==args->threadno){  //every thread will check this condition to find on which block it has to operate
         for(int k = i;k<i+16;k++){
           for(int l = j;l<j+16;l++){
             /*rowA = k;
             colA = l;
             rowB = l;
             colB = N-1-k;*/
            *((args->arr)+k+l) += A[k * N + l] * B[l * N + (N-k-1)]; //matrix multiplication
           }
         }
       }
     }
   }
   pthread_exit(0);
}
void multiThread(int N, int *matA, int *matB, int *output)
{
//   for(int i = 0;i < 2*N-1;i++){
  //     output[i] = 0;
   //}
   
   //Initializing global variables
   ::N = N;
   A = matA;
   B = matB;
   ::output = output;
  
   struct struct_thrd args[num_threads];    //structure for every thread
   
   pthread_t tids[num_threads];             //pthread array
   for(int i = 0 ; i < num_threads;i++)
   {
      args[i].threadno = i;
      pthread_create(&tids[i],NULL,mul,&args[i]);  //thread creation and calling mul function
      
   }   
    //Wait until all threads are completed  
   for(int i = 0; i<num_threads;i++){
   
        pthread_join(tids[i],NULL);
        for(int j = 0;j<2*N-1;j++){
            output[j] += args[i].arr[j];  // multiplying all the arrays obtained from the threads to get final output array
            
       }
   }  
}
