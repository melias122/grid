#include "app.h"

#include "mpi.h"

#include <cassert>
#include <typeinfo>

Application::Application(int argc, char** argv)
{
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &m_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &m_rank);
}

Application::~Application() { MPI::Finalize(); }

int Application::rank() { return m_rank; }

int Application::size() { return m_size; }

template <typename T>
MPI_Datatype get_datatype()
{
    if (typeid(T) == typeid(char)) {
        return MPI_CHAR;
    } else if (typeid(T) == typeid(int)) {
        return MPI_INT;
    } else {
        assert(MPI_UNDEFINED);
    }
    return 0;
}

template <typename T>
void comm<T>::send(int dest, int tag, const T& data, int size)
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
    MPI_Recv(&t, size, get_datatype<T>(), source, tag, MPI_COMM_WORLD,
        MPI_STATUS_IGNORE);
    std::cout << MPI::COMM_WORLD.Get_rank() << " got " << t << std::endl;
    return t;
}

void sendString(int dest, int tag, const std::string& s)
{
    std::cout << "Debug/sendString: send " << s << " to: " << dest
              << " tag: " << tag << std::endl;

    MPI_Send(&s[0], s.size(), MPI_CHAR, dest % MPI::COMM_WORLD.Get_size(), tag,
        MPI_COMM_WORLD);
}

std::string recvString(int source, int tag)
{
    int strlen;
    MPI_Status status;

    source %= MPI::COMM_WORLD.Get_size();

    MPI_Probe(source, tag, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_CHAR, &strlen);

    std::string s(strlen, 0);
    MPI_Recv(&s[0], // ok in c++11
        s.size(), MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    std::cout << "Debug/recvString: recv " << s << " from: " << source
              << " tag: " << tag << std::endl;

    return s;
}
