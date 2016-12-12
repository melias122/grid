#include "app.h"

#include "mpi.h"

#include <typeinfo>

Application::Application()
{
	MPI::Init();
	m_size = MPI::COMM_WORLD.Get_size();
	m_rank = MPI::COMM_WORLD.Get_rank();
}


Application::Application(int &argc, char **&argv)
{
	MPI::Init(argc, argv);
	m_size = MPI::COMM_WORLD.Get_size();
	m_rank = MPI::COMM_WORLD.Get_rank();
}

Application::~Application()
{
	MPI::Finalize();
}

int Application::rank()
{
	return m_rank;
}

int Application::size()
{
	return m_size;
}

template <typename T>
MPI_Datatype get_datatype()
{
	if (typeid(T) == typeid(char)) {
		return MPI_CHAR;
	}
	if (typeid(T) == typeid(int)) {
		return MPI_INT;
	}
	return 0;
}


template <typename T>
void comm<T>::send(int dest, int tag, const T &data, int size)
{
	dest %= MPI::COMM_WORLD.Get_size();
	std::cout << MPI::COMM_WORLD.Get_rank() << " sending " << data << std::endl;
	MPI_Send(&data, size, get_datatype<T>(), dest, tag, MPI_COMM_WORLD);
}

template <typename T>
T comm<T>::recv(int source, int tag, int size) const
{
	source %= MPI::COMM_WORLD.Get_size();
	T t;
	MPI_Recv(&t, size, get_datatype<T>(), source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	std::cout << MPI::COMM_WORLD.Get_rank() << " got " << t << std::endl;
	return t;
}
