#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int M0[2][2];
int M_cur[2][2];
int input_matrix[1][2];
int output_matrix[1][2];


int main(int argc, char *argv[]){
  int Xi;
  int a = 55;
  int b = 66;
  int X0 = 777;
  int p = 1457999;
  //int n = 2; 
	
  struct timeval t1, t2;

  //check if there is input
  if(argc < 2){
	printf("give input of how many random number to generate");
  }
  else{
    
  int n = atoi(argv[1]);

  //initialize matrix
  M_cur[0][0] = M0[0][0] = a;
  M_cur[1][0] = M0[1][0] = b;
  M_cur[0][1] = M0[0][1] = 0;
  M_cur[1][1] = M0[1][1] = 1;
  input_matrix[0][0] = X0;
  input_matrix[0][1] = 1;

  int *rand_array = (int*) malloc(sizeof(int) * n);
  //time
  gettimeofday(&t1, NULL);

  //first run
  Xi = ((a * X0) + b) % p;
  rand_array[0] = Xi;

  for(int i = 1; i < n; i++){
	Xi = ((a * rand_array[i-1]) + b) % p;
	rand_array[i] = Xi;
  }

  gettimeofday(&t2, NULL);
 
  int ttime = ((t2.tv_sec - t1.tv_sec) * 1000000 ) + (t2.tv_usec - t1.tv_usec);
  printf("serial run time = %d microseconds\n", ttime);
  }
}
