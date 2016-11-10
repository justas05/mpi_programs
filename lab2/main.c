#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	int rank, namelen, n;
	//char hostname[256];
	//char proc_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &n);

	//MPI_Get_processor_name(proc_name, &namelen);
	//gethostname(hostname, 255);

	MPI_Comm MY_COMM;
	int color;
	
	switch(rank)
	{
	    case 0: case 3: case 5: case 6:
		color = 0;
		break;
	    case 2: case 4: case 8:
		color = 1;
		break;
	    default:
		color = 3;
		break;
	}
	
	MPI_Comm_split(MPI_COMM_WORLD, color, 1, &MY_COMM);

	int new_rank;
	int n2;

	MPI_Comm_rank(MY_COMM, &new_rank);
	MPI_Comm_size(MY_COMM, &n2);

	printf("MPI_COMM_WORLD:\n\tprocess: %d\n\trank: %d\nMY_COMM:\n\tprocess: %d\n\trank: %d\n\n", n, rank, n2, new_rank);

	MPI_Finalize();

	return 0;
}
