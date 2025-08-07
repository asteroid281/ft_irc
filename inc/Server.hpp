#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include <iostream>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <fcntl.h>
# include <poll.h>
# include <csignal>
# include <cstring>

# define MAX_CLIENTS 100
# define BUFFER_SIZE 512

using	std::vector;
using	std::map;
using	std::runtime_error;

class	Client;
class	Channel;

class	Server
{
	private:
		vector<struct pollfd>	_fds;
		map<string, Channel*>	_channels;
		map<int, Client*>		_clients;
		string	_serverName;
		string	_version;
		string	_creationDate;
		string	_password;
		bool	_running;
		int		_port;
		int		_serverSocket;
		bool	setupSocket(void);
		bool	acceptNewClient(void);
		void	handleClientMessage(int clientFd);
		void	removeClient(int clientFd);
		void	processCommand(Client* client, const string& message);
	public:
		Server(int port, const string& password);
		~Server();
		void			start(void);
		void			stop(void);
		// Getters
		const string&	getPassword(void) const;
		const string&	getServerName(void) const;
		const string&	getVersion(void) const;
		const string&	getCreationDate(void) const;
		// Client management
		Client*			getClient(int fd);
		Client*			getClientByNick(const string& nickname);
		void			removeClient(Client* client);
		// Channel management
		Channel*		getChannel(const string& name);
		Channel*		createChannel(const string& name, Client* creator);
		void			removeChannel(const string& name);
		// Message broadcasting
		void			broadcastToChannel(const string& channelName, const string& message, Client* sender = NULL);
		void			sendToClient(int fd, const string& message);
		// Utility
		bool			isValidNickname(const string& nickname);
		vector<string>	getChannelList(void);
};

#endif
