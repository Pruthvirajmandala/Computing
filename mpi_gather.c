#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main (int argc, char *argv[])
{
int numtasks, rank, P,maxi=999,mini=0,i,sum,avg;
int *result;
srand(time(0));//it creates variations due to processor rank

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks);//gets total number of processors
MPI_Comm_rank(MPI_COMM_WORLD, &rank);//gets total number of processors
result = (int *)malloc(sizeof(int) * numtasks );
P = (rand() % (maxi - mini + 1)) + mini;
printf(" Processor  %d: number=%d \n ",rank,P);
MPI_Barrier(MPI_COMM_WORLD);
//Calculate Sum using MPI_Gather group function directy
//MPI_Gather (constvoid&sendbuf,int send count,mpi datatype sendtype,void &recvbuf,count,datatype,int root,mpi_comm)
MPI_Gather( &P, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD); 
//updates sum of root processor
if (rank == 0) {
    sum =0 ;
    for(i=0;i< numtasks;i++){
       sum = sum +result[i];
    }
//root processor calculates average
    avg = sum/numtasks;
//root processor prints output
    printf(" sum of %d processors  = %d Average = %d\n\n",numtasks,sum,avg);
}

MPI_Finalize();
}
