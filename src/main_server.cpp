#include "main_server.hpp"

int main()
{
	TCP_Server server;
	server.ListenLoop();
	return 0;
}