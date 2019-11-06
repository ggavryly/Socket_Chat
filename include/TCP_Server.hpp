#pragma once

#include "main_server.hpp"
#include "My_Unordered_Map.hpp"
#define BUF_SIZE 1024

class TCP_Server
{
	public:
		TCP_Server();
		TCP_Server(TCP_Server const &);
		~TCP_Server();
	
	public:
		std::pair<int, std::string>	Login(int client);
		void						ListenLoop();
		void						ClientsDispatch();
		void						FillSetFd();
		void						AcceptConnection();
		void						CloseConnection(int client);
		int							SetNBlock(int fd);
	
	private:
		int										server_socket;
		My_Unordered_Map						client_sockets;
		std::array<char, BUF_SIZE>				buffer;
		struct fd_set							set_fd;
		struct sockaddr_in						sock_addr;
};
