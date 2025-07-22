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

void	Client::setNickname(const string& nickname)
{
	this->_nickname = nickname;
}

void	Client::setUsername(const string& username)
{
	this->_username = username;
}

void	Client::setRealname(const string& realname)
{
	this->_realname = realname;
}

void	Client::setHostname(const string& hostname)
{
	this->_hostname = hostname;
}

void	Client::setAuthenticated(bool auth)
{
	this->_authenticated = auth;
}

void	Client::setRegistered(bool reg)
{
	this->_registered = reg;
}

string	Client::extractMessage()
{
	string	message;
	size_t	pos;

	pos = this->_buffer.find("\r\n");
	if (pos == string::npos)
		return string("");
	message = this->_buffer.substr(0, pos);
	this->_buffer.erase(0, pos + 2);
	return (message);
}

void	Client::appendToBuffer(const string& data)
{
	this->_buffer += data;
}

void	Client::clearBuffer()
{
	this->_buffer.clear();
}

void	Client::joinChannel(const string& channelName)
{
	this->_channels.insert(channelName);
}

void	Client::leaveChannel(const string& channelName)
{
	this->_channels.erase(channelName);
}

bool	Client::isInChannel(const string& channelName) const
{
	return (this->_channels.find(channelName) != this->_channels.end());
}

string	Client::getPrefix() const
{
	return (string(":" + this->_nickname + "!" + this->getFullName()));
}

string	Client::getFullName() const
{
	return (this->_username + "@" + this->_hostname);
}
