#include "Client.hpp"

Client::Client(int fd)
{}

Client::~Client()
{}

bool	Client::isRegistered() const
{
	return (this->_registered);
}

bool	Client::isAuthenticated() const
{
	return (this->_authenticated);
}

int		Client::getFd() const
{
	return (this->_fd);
}

const string&	Client::getNickname() const
{
	return (this->_nickname);
}

const string&	Client::getUsername() const
{
	return (this->_username);
}

const string&	Client::getRealname() const
{
	return (this->_realname);
}

const string&	Client::getHostname() const
{
	return (this->_hostname);
}

const string&	Client::getBuffer() const
{
	return (this->_buffer);
}

const std::set<string>&	Client::getChannels() const
{
	return (this->_channels);
}
