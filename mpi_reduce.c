#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
int genRandom(int min, int max, int rank);
int main(int argc, char* argv[]) {
int myrank, numtasks, number;
int root = 0;
int sum = 0; //initial sum=0
float average;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numtasks); //gets total number of processors
MPI_Comm_rank(MPI_COMM_WORLD, &myrank); //gets own rank
//all processors generating a random integer in the specified range
number = genRandom(200, 299, myrank);

//Checking all numbers
printf("\nProcessor %d: number=%d",myrank,number);
MPI_Barrier(MPI_COMM_WORLD);

//Calculate Sum using MPI_Reduce group function directy
//MPI_Reduce (&sendbuf,&recvbuf,count,datatype,op,root,comm)
MPI_Reduce(&number, &sum, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
//updates sum of root processor.
if (myrank == root) {
//root processor calculates average
average = (float)sum / (float)numtasks;
//root processor prints output
printf("\nSum of %d Processors's Numbers=%d", numtasks, sum);
printf("\nAverage of %d Processors's Numbers=%f\n", numtasks, average);
}
MPI_Finalize();
return 0;
}
int genRandom(int min, int max, int rank) {
srand((rank + 1) * time(NULL)); //creating variations due to processor rank
return (rand() % (max + 1 - min)) + min;
}
