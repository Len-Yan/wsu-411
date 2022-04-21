#!/bin/sh
mpirun -np 2 ./a.out 64
mpirun -np 2 ./a.out 128
mpirun -np 2 ./a.out 256
mpirun -np 2 ./a.out 512
mpirun -np 2 ./a.out 1024
mpirun -np 2 ./a.out 2048
mpirun -np 2 ./a.out 4096
mpirun -np 2 ./a.out 8192
mpirun -np 2 ./a.out 16384
mpirun -np 2 ./a.out 32768
mpirun -np 2 ./a.out 65536
mpirun -np 2 ./a.out 131072
mpirun -np 2 ./a.out 262144
mpirun -np 2 ./a.out 524288


