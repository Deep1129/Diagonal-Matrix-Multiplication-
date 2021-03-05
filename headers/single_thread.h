void singleThread(int N, int *matA, int *matB, int *output)
{
    //int bs = 16;
    //first two for loops are to access matrices block wise

   for(int i = 0 ; i < N;i += 16)
   {
     for(int j = 0; j <N;j +=16)
     {
         /*Following two for loops are to access elements within            a block*/
         for(int k = i;k<i+16;k++){
         	
           for(int l = j;l<j+16;l++){
             /* rowA = k;
             colA = l;
             rowB = l;
             colB = N-k-1;*/
             output[k+l]+= matA[k * N + l] * matB[l* N + (N-k-1)];
         }
       }
     }
   }

 }

