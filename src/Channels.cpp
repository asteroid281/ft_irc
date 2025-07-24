#include "Channel.hpp"

Channel::Channel(const string& name)
{
	this->_name = name;
}

Channel::~Channel()
{}

size_t	Channel::getClientCount() const
{
	return (this->_clients.size());
}

bool	Channel::isInviteOnly() const
{
	return (this->_inviteOnly);
}

bool	Channel::isTopicRestricted() const
{
	return (this->_topicRestricted);
}

bool	Channel::hasPassword() const
{
	return (this->_hasPassword);
}

int		Channel::getUserLimit() const
{
	return (this->_userLimit);
}

const string&	Channel::getName() const
{
	return (this->_name);
}

const string&	Channel::getTopic() const
{
	return (this->_topic);
}

const string&	Channel::getPassword() const
{
	return (this->_password);
}

const set<Client*>&	Channel::getClients() const
{
	return (this->_clients);
}

const set<Client*>&	Channel::getOperators() const
{
	return (this->_operators);
}

void	Channel::setTopic(const string& topic)
{
	this->_topic = topic;
}

void	Channel::setPassword(const string& password)
{
	this->_password = password;
	this->_hasPassword = !password.empty();
}

void	Channel::setInviteOnly(bool inviteOnly)
{
	this->_inviteOnly = inviteOnly;
}

void	Channel::setTopicRestricted(bool topicRestricted)
{
	this->_topicRestricted = topicRestricted;
}

void	Channel::setUserLimit(int limit)
{
	this->_userLimit = limit;
}

void	Channel::addClient(Client* client)
{
	if (client)
		this->_clients.insert(client);
}

void	Channel::removeClient(Client* client)
{
	if (client)
		this->_clients.erase(client);
}

bool	Channel::hasClient(Client* client) const
{
	return (client && this->_clients.find(client) != this->_clients.end());
}

bool	Channel::hasClient(const string& nickname) const
{
	const set<Client*>::iterator	it;

	it = this->_clients.begin();
	while (it != this->_clients.end()) 
	{
		if ((*it)->getNickname() == nickname)
			return (true);
		++it;
	}
	return (false);
}

void	Channel::addOperator(Client* client)
{
	if (client)
		this->_operators.insert(client);
}

void	Channel::removeOperator(Client* client)
{
	if (client)
		this->_operators.erase(client);
}

bool	Channel::isOperator(Client* client) const
{
	return (client && this->_operators.find(client) != this->_operators.end());
}

bool	Channel::isEmpty() const
{
	return (this->_clients.empty());
}

string	Channel::getClientList() const
{
	set<Client*>::iterator	it;
	string					list;

	while (it != this->_clients.end())
		list += string(it != this->_clients.begin(), " ") + (*it)->getNickname();
	return (list);
}
