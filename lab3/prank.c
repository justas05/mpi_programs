#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int rank, size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int sendbuf;
	int recvbuf[5] = {0};

	sendbuf = rank;	

	printf("BEFORE BCAST. rank %d. Result: %d %d %d %d %d\n", rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3], recvbuf[4]);

	MPI_Gather(&sendbuf, 1, MPI_INT, recvbuf, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("AFTER BCAST. rank %d. Result: %d %d %d %d %d\n", rank, recvbuf[0], recvbuf[1], recvbuf[2], recvbuf[3], recvbuf[4]);


	MPI_Finalize();

	return 0;
}
