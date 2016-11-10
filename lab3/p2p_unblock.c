#include "mpi.h"
#include <stdio.h>
#nclude <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int rank;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	

	char msg[20];
	char recv_buf[20];

	if (rank == 0)
	{
		strcpy(msg, "Hello from 0");
		
		MPI_Isend(msg, strlen(msg) + 1, MPI_CHAR, 1, 99, MPI_COMM_WORLD, &request);
		MPI_Irecv(recv_buf, 20, MPI_CHAR, 1, 99, MPI_COMM_WORLD, &request);

		MPI_Wait(&request, &status);

		printf("recv rank %d. Result: %s\n", rank, recv_buf);
	}	
	else if (rank == 1)
	{
		strcpy(msg, "hello from 1");

		MPI_Isend(msg, strlen(msg) + 1, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &request);
		MPI_Irecv(recv_buf, 20, MPI_CHAR, 0, 99, MPI_COMM_WORLD, &request);
		
		MPI_Wait(&request, &status);

		printf("recv rank %d. Result: %s\n", rank, recv_buf);
	}

	MPI_Finalize();

	return 0;
}
