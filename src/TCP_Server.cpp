
#include "TCP_Server.hpp"

TCP_Server::TCP_Server()
{
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP_STREAM
	sock_addr.sin_family = AF_INET; // IPv4
	sock_addr.sin_port = htons(4257); // Port 4257
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 127.0.0.1
	bind(server_socket, (struct sockaddr *)(&sock_addr), sizeof(sock_addr)); // Bind server_socket
	SetNBlock(server_socket); // Set socket to non-blocking mode
	listen(server_socket, SOMAXCONN); // Init max connections
}

int TCP_Server::SetNBlock(int fd)
{
	int	flags;
	#if defined(O_NONBLOCK)
		if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
			flags = 0;
		return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
	#else
		flags = 1;
		return ioctl(fd, FIONBIO, &flags);
	#endif
}

TCP_Server::TCP_Server(TCP_Server const &)
{}

TCP_Server::~TCP_Server()
{
	shutdown(server_socket, SHUT_RDWR);
	close(server_socket);
}

void TCP_Server::FillSetFd()
{
	FD_ZERO(&set_fd);
	FD_SET(server_socket, &set_fd);// Adding server socket to Set list
	for (auto const & it: client_sockets) // Adding clients socket to Set list
		FD_SET(it.first, &set_fd);
}

void TCP_Server::CloseConnection(int client)
{
		shutdown(client, SHUT_RDWR);
		close(client);
}

void TCP_Server::ClientsDispatch()
{
	for (auto it = client_sockets.begin(), end = client_sockets.end(); it != end;)
	{
		buffer.fill('\0');
		if (FD_ISSET(it->first, &set_fd))
		{
			
			int recv_size = recv(it->first, buffer.data(), BUF_SIZE, 0);
			
			// If no message or interruption on signal - close connection
			if (recv_size <= 0 && errno != EAGAIN)
			{
				CloseConnection(it->first);
				it = client_sockets.erase(it);
				continue;
			}
			else if (recv_size > 0 && it->second == "") // Your first word will be your nickname
			{
				it->second = buffer.data();
				it->second.erase(it->second.size() - 1);
				it->second += ":";
			}
			// Sending message all connected clients
			else if (recv_size > 0)
			{
				std::string tmp = it->second;
				tmp += buffer.data();
				for(auto const & elem: client_sockets)
				{
					if (elem.first != it->first)
						send(elem.first, tmp.c_str(), tmp.size(), 0);
				}
			}
		}
		buffer.fill('\0');
		it++;
	}
}

void TCP_Server::AcceptConnection()
{
	if (FD_ISSET(server_socket, &set_fd))
	{
		int client_socket = accept(server_socket, nullptr, nullptr);
		if (client_socket != -1)
		{
			std::pair<int, std::string> response;
			SetNBlock(client_socket); // Set to non-blocking mode on client socket
			response = Login(client_socket);
			if (response.first != -1)
				client_sockets.Insert(response.first, response.second); // Put id to std::unordered_map with nickname
		}
	}
}

void TCP_Server::ListenLoop()
{
	while (true)
	{
		// Add server and clients sockets
		FillSetFd();
		
		// Getting max socket index for defining end Bit in Set list. Otherwise, need to go thru whole Set list(1024 bits).
		int max = std::max(server_socket, client_sockets.GetMax());
		
		// Waiting for someone event
		select(max + 1, &set_fd, nullptr, nullptr, nullptr);
		
		// Sending message all connected clients or close connection (Interaction only with client sockets)
		ClientsDispatch();
		// There can only be an event - request to accept the connection
		AcceptConnection();
	}
}

std::pair<int, std::string> TCP_Server::Login(int client)
{
	std::pair<int, std::string>		response;
	send(client, "Welcome to the chat\n", 20, 0); // Greetings
	response.first = client;
	response.second = "";
	return response;
}