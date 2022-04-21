#include <stdio.h>
#include <mpi.h>
#include <assert.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int rank, p;
  struct timeval t1, t2;
  int Sendm = 24;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&p);

  printf("my rank=%d\n",rank);
  printf("Rank=%d: number of processer =%d\n",rank,p);

  assert(p>=2);   

  if(rank == 1){
    int dest = 0;
    
    for(int i = 0; i < Sendm; i++){
      int number = 1 << i; 
      char *send = (char*) malloc(sizeof(char)*number);

      gettimeofday(&t1, NULL); 
      MPI_Send(send, number, MPI_CHAR, dest, 0, MPI_COMM_WORLD); 
      gettimeofday(&t2,NULL); 
      int tsend = (t2.tv_sec-t1.tv_sec) * 1000000 + (t2.tv_usec-t1.tv_usec);

      printf("-Rank=%d: sent message    %d to rank %d; Send time   %d microseconds\n",rank, number, dest, tsend);
    }
  }
  else if (rank == 0){

    for(int i = 0; i < Sendm; i++){
      MPI_Status status;
      int number = 1 << i; 

      char *rcv = (char*) malloc(sizeof(char)*number);
      memset(rcv, 'z', number);
      gettimeofday(&t1, NULL); 
      MPI_Recv(rcv, number, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      gettimeofday(&t2,NULL); 
      int trecv = (t2.tv_sec-t1.tv_sec) * 1000000 + (t2.tv_usec-t1.tv_usec);

      printf("-Rank=%d: receive message %d from rank %d; Recv time %d microseconds\n\n",rank, number , status.MPI_SOURCE, trecv);
    }
  }

  MPI_Finalize();
}


