#include "Server.hpp"

Server::Server(int port, const string& password)
{}

Server::~Server()
{}

const string&	Server::getPassword() const
{
	return (this->_password);
}

const string&	Server::getServerName() const
{
	return (this->_serverName);
}

const string&	Server::getVersion() const
{
	return (this->_version);
}

const string&	Server::getCreationDate() const
{
	return (this->_creationDate);
}

Client*	Server::getClient(int fd)
{
	map<int, Client*>::iterator	it;

	it = this->_clients.find(fd);
	if (it != this->_clients.end())
		return (it->second);
	return (nullptr);
}

Client*	Server::getClientByNick(const string& nickname)
{
	map<int, Client*>::iterator	it;

	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getNickname() == nickname)
			return (it->second);
		++it;
	}
	return (nullptr);
}

void Server::removeClient(Client* client)
{
	int fd;

	if (client)
	{
		fd = client->getSocketFd();
		this->_clients.erase(fd);
		close(fd);
		delete (client);
	}
}

Channel*	Server::getChannel(const string& name)
{
	map<string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it != this->_channels.end())
		return (it->second);
	return (nullptr);
}

Channel*	Server::createChannel(const string& name, Client* creator)
{
	Channel*	channel;

	channel = new Channel(name, creator);
	this->_channels[name] = channel;
	return (channel);
}

void	Server::removeChannel(const string& name)
{
	map<string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it != this->_channels.end())
	{
		delete (it->second);
		this->_channels.erase(it);
	}
}

vector<string>	Server::getChannelList()
{
	map<string, Channel*>::iterator	it;
	vector<string>					channelList;

	it = this->_channels.begin();
	while (it != this->_channels.end())
	{
		channelList.push_back(it->first);
		++it;
	}
	return (channelList);
}
