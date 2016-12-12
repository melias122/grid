#ifndef APP_H
#define APP_H

class Application
{
public:
	Application();
	Application(int &argc, char **&argv);
	~Application();

	int rank();
	int size();
private:
	int m_rank, m_size;
};

struct Bruteforcer
{
	~Bruteforcer() {}
	virtual void run(int procId, int nproc) = 0;
};

struct Runner
{
	Runner() = delete;

	static void run(Bruteforcer *b)
	{
		Application app;
		b->run(app.rank(), app.size());
	}
};

// experimental communicator
template <typename T>
struct comm
{
public:
	void send(int dest, int tag, const T &data, int size = 1);
	T recv(int source, int tag, int size = 1) const;
};

template struct comm<char>;
template struct comm<int>;

#endif // APP_H
