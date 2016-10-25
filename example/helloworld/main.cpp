#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv);

	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	char proccesor_name[MPI_MAX_PROCESSOR_NAME];
	int name_len;
	MPI_Get_processor_name(proccesor_name, &name_len);

	printf("Hello proccessor %s, rank %d, out of %d world proccesors\n", proccesor_name, world_rank, world_size);

	MPI::Finalize();
	return 0;
}
