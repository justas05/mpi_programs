#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main(int argc, char** argv)
{
	int rank, size;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int *recv = (int*)malloc(size * sizeof(int));
	int *proc = (int*)malloc(size * sizeof(int));

	memset(recv, -1, size * sizeof(int));
	memset(proc, -1, size * sizeof(int));

	int i;
	for(i = 0; i < size; ++i)
		proc[i] = i;

	for(i = 0; i < size; ++i)
	{
		int j;
		for(j = 0; j < size; ++j)
		{
			if (i == j)
			{
				if (i == rank)
					recv[i] = rank;
				continue;
			}

			if(i == rank)
				MPI_Send(&rank, 1, MPI_INT, j, 99, MPI_COMM_WORLD);
			else if (j == rank)
				MPI_Recv(&recv[i], 1, MPI_INT, i, 99, MPI_COMM_WORLD, &status);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}

	for (i = 0; i < size; ++i)
		printf("rank %d - %d ", rank, recv[i]);
	printf("\n");

	MPI_Finalize();

	free(recv);
	free(proc);

	return 0;
}
