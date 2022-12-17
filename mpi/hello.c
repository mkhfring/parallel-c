#include <stdio.h>
#include <mpi.h>

const int LEN = 100;
int main() {
char msg[LEN]; // String storing message
int comm_sz, my_rank;
MPI_Init(NULL, NULL);
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); // get communicator size
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // get my rank
if (my_rank != 0) { //Everyone EXCEPT Process 0
//Create and send message to process 0
    sprintf(msg, "Greetings from process %d of %d!", my_rank, comm_sz);
    MPI_Send(msg, LEN, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

} else { //ONLY Process 0
printf("Hi from process %d of %d!\n",my_rank,comm_sz); // Print my message
for (int q = 1; q < comm_sz; q++) { // Print others’ messages
    MPI_Recv(msg, LEN, MPI_CHAR, q, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    printf("%s\n", msg);

}
}
MPI_Finalize();
return 0;
}