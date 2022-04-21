#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

int M0[2][2];
int M_cur[2][2];
int input_matrix[1][2];
int output_matrix[1][2];
int p;

struct timeval t1, t2;
int rank;

//calculation
void calcurrent_matrix(int power){
  int temp[2][2];
  int i;
 
  for(i = 1; i < power; i++){
	temp[0][0] = (M_cur[0][0] * M0[0][0]) + (M_cur[0][1] * M0[1][0]);
	temp[1][0] = (M_cur[1][0] * M0[0][0]) + (M_cur[1][1] * M0[1][0]);
	temp[0][1] = (M_cur[0][0] * M0[0][1]) + (M_cur[0][1] * M0[1][1]);
	temp[1][1] = (M_cur[1][0] * M0[0][1]) + (M_cur[1][1] * M0[1][1]);
	M_cur[0][0] = temp[0][0];
	M_cur[1][0] = temp[1][0];
	M_cur[0][1] = temp[0][1];
	M_cur[1][1] = temp[1][1];
  }
}
// find ini matrix val
int starter(){
  return ((input_matrix[0][0] * M_cur[0][0]) + (input_matrix[0][1] * M_cur[1][0]));
}

//run with input
int main(int argc, char *argv[]){
  int Xi;
  int a = 55;
  int b = 66;
  int X0 = 777;
  int p = 1457999;
  int P = 1457999;
  int index;

  //check if there is input
  if(argc < 2){
	printf("give input of how many random number to generate");
  }
  else{
  //ini
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  index = (n/p) * (rank);
 
  int n = atoi(argv[1]);
 
  M_cur[0][0] = M0[0][0] = a;
  M_cur[1][0] = M0[1][0] = b;
  M_cur[0][1] = M0[0][1] = 0;
  M_cur[1][1] = M0[1][1] = 1;

  input_matrix[0][0] = X0;
  input_matrix[0][1] = 1;

  int *rand_array = (int*) malloc(sizeof(int) * (n/p));

  // time
  gettimeofday(&t1, NULL);

  //first run
  calcurrent_matrix(index);
 
  Xi = starter();
  rand_array[0] = Xi;

  for(int i = 1; i < (n/p); i++){
	Xi = ((a * rand_array[i-1]) + b) % P;

	rand_array[i] = Xi;
  }

  gettimeofday(&t2, NULL);

  int ttime = ((t2.tv_sec - t1.tv_sec) * 1000000 ) + (t2.tv_usec - t1.tv_usec);

  if(rank == 0){
	printf("run time= %d\n", ttime);
  }

  MPI_Finalize();
  }
}
