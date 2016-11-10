#include "mpi.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <time.h>


int usage(char*);
int check_options(int*, char**, int*);
int make_op(char*, int, int, int**, int**, int, int, MPI_Status*, MPI_Request*, MPI_Comm);


int main(int argc, char** argv)
{
	srand(time(NULL));
	
	int op = 0; 
	int i;
	
	check_options(&argc, argv, &op);

	int rank, size;
	MPI_Status status;
	MPI_Request request;

	MPI_Init(&argc, &argv);	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int *send_buf = (int*)malloc(size * sizeof(int));
	int *recv_buf = (int*)malloc(size * sizeof(int));
	int size_str_buf = 2048;
	char* str_buf = (char*)malloc(size_str_buf);

	memset(send_buf, 0, size * sizeof(int));
	memset(recv_buf, 0, size * sizeof(int));
	memset(str_buf, '\0', size_str_buf);

	
	sprintf(str_buf, "op - %d\n", op);

	
	for (i = 0; i < size; ++i)
		send_buf[i] = (rand() + rank) % 100;
	
	sprintf(str_buf, "rank %d, send_buf: ", rank);
	for (i = 0; i < size; ++i)
		sprintf(str_buf, "%s %d", str_buf, send_buf[i]);


	make_op(argv[0], op, 0, &send_buf, &recv_buf, size, rank, &status, &request, MPI_COMM_WORLD);

	
	sprintf(str_buf, "%s\nrecv_buf: ", str_buf);
	for (i = 0; i < size; ++i)
		sprintf(str_buf, "%s %d", str_buf, recv_buf[i]);
	sprintf(str_buf, "%s\n\n", str_buf);

	

	printf(str_buf);
	
	free(send_buf);
	if (op != 1)
		free(recv_buf);
	free(str_buf);

	MPI_Finalize();

	return 0;
}


int usage(char* prog_name)
{
	printf("usage: %s [options]\n\
		-b \t\tBroadcast\n\
		-g \t\tGather\n\
		-s \t\tScatter\n\
		-a \t\tAllGather\n\
		-A \t\tAllToAll\n\
		-r \t\tReduce\n\
		-R \t\tAllReduce\n\
		-S \t\tReduceScatter\n\
		-c \t\tScan\n",prog_name);
	return 0;
}

int make_op(char* prog, int op, int root, int** send, int** recv, int size, int rank, MPI_Status* status, MPI_Request* request, MPI_Comm comm)
{
	int* count = (int*)malloc(size * sizeof(int));
	//memset(count, 1, size * sizeof(int));
	
	int i;
	for (i = 0; i < size; ++i)
		count[i] = 1;

	switch(op)
	{
	case 0:
		usage(prog);
		return 0;
	case 1:
		free(*recv);
		*recv = *send;

		MPI_Bcast(*send, 1, MPI_INT, root, comm);

		break;
	case 2:
		MPI_Gather(*send, 1, MPI_INT, *recv, 1, MPI_INT, root, comm);
		break;
	case 4:
		MPI_Scatter(*send, 1, MPI_INT, *recv, 1, MPI_INT, root, comm);
		break;
	case 8:
		MPI_Allgather(*send, 1, MPI_INT, *recv, 1, MPI_INT, comm);
		break;
	case 16:
		MPI_Alltoall(*send, 1, MPI_INT, *recv, 1, MPI_INT, comm);
		break;
	case 32:
		MPI_Reduce(*send, *recv, size, MPI_INT, MPI_SUM, root, comm);
		break;
	case 64:
		MPI_Allreduce(*send, *recv, size, MPI_INT, MPI_SUM, comm);
		break;
	case 128:
		MPI_Reduce_scatter(*send, *recv, count, MPI_INT, MPI_SUM, comm);
		break;
	case 256:
		MPI_Scan(*send, *recv, size, MPI_INT, MPI_SUM, comm);
		break;
	}
	free(count);
	return 0;
}

int check_options(int *argc, char** argv, int *op)
{
	int opt;
	while((opt = getopt(*argc, argv, "hbgsaArRSc")) != -1)
	{
		switch(opt)
		{
			case 'h':
				*op = 0;
				break;
			case 'b':
				*op = (1 << 0);
				break;
			case 'g':
				*op = (1 << 1);
				break;
			case 's':
				*op = (1 << 2);
				break;
			case 'a':
				*op = (1 << 3);
				break;
			case 'A':
				*op = (1 << 4);
				break;
			case 'r':
				*op = (1 << 5);
				break;
			case 'R':
				*op = (1 << 6);
				break;
			case 'S':
				*op = (1 << 7);
				break;
			case 'c':
				*op = (1 << 8);
				break;
		}
	}
	
	return 0;
}
