#include "mpi.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int buf;

	if (rank == 0)
		buf = 777; 

	printf("BEFORE BCAST. rank %d. Result: %d\n", rank, buf);

	MPI_Bcast(&buf, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("AFTER BCAST. rank %d. Result: %d\n", rank, buf);

	MPI_Finalize();

	return 0;
}
