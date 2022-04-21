#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


//returns 1 if inside
// find inside circle or not by pythagorean 
int circle(double x, double y){
  double dx = (x - 0.5);
  double dy = (y - 0.5);
  if ( (dx*dx) + (dy*dy) <= 0.25 ){
    return 1;
  }
  else{ return 0;}
}

// get random value between 0,1
double rand_xy(){
  return (double) rand() / RAND_MAX;
}



//main program
int main(int argc, char *argv[]){
  //input
  
  if(argc < 3){
    printf("need input n(iterations) and p(threads)\n");
    exit(1);
  }

  int n = atoi(argv[1]);
  int p = atoi(argv[2]);

  double x;
  double y;
  int count = 0;
  int i = 0;

  
  omp_set_num_threads(p);


#pragma omp parallel
  {
     //check if able to get p threads
    assert(p==omp_get_num_threads());
    //printf("number of threads set = %d\n", omp_get_num_threads());
    
    int rank = omp_get_thread_num();
    //printf("Rank = %d; iterations(n) = %d ;threads(p) = %d \n", rank, n, p);
  }
  

  
  //actuall run
  double time = omp_get_wtime();
omp_set_num_threads(p);
#pragma omp parallel for default(shared) private(i,x,y) reduction(+: count)
  
  for(i = 0; i < n; i++){
    x = rand_xy();
    y = rand_xy();
    if(circle(x,y)){
      count += 1;
    }
  }

  //estimate pi
  double fraction = (double)count / n;
  double mypi = 4 * fraction;

  // actuall run end
  time = omp_get_wtime() - time;

  printf("run time = %.5f s \n", time);
  printf("estimate pi value =  %.20f \n", mypi);
}

