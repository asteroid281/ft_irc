#include "Channel.hpp"

Channel::Channel(const string& name)
{
	this->_name = name;
}

Channel::~Channel()
{}

size_t	Channel::getClientCount(void) const
{
	return (this->_clients.size());
}

bool	Channel::isInviteOnly(void) const
{
	return (this->_inviteOnly);
}

bool	Channel::isTopicRestricted(void) const
{
	return (this->_topicRestricted);
}

bool	Channel::hasPassword(void) const
{
	return (this->_hasPassword);
}

int		Channel::getUserLimit(void) const
{
	return (this->_userLimit);
}

const string&	Channel::getName(void) const
{
	return (this->_name);
}

const string&	Channel::getTopic(void) const
{
	return (this->_topic);
}

const string&	Channel::getPassword(void) const
{
	return (this->_password);
}

const set<Client*>&	Channel::getClients(void) const
{
	return (this->_clients);
}

const set<Client*>&	Channel::getOperators(void) const
{
	return (this->_operators);
}

const set<Client*>&	Channel::getBanned(void) const
{
	return (this->_banned);
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

bool	Channel::isEmpty(void) const
{
	return (this->_clients.empty());
}

void	Channel::broadcast(const string& message, Client *sender)
{
	set<Client*>::iterator	it;

	if (this->_clients.empty())
		return ;
	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (*it != sender)
			this->sendToClient((*it)->getFd(), message);
		++it;
	}
}

string	Channel::getClientList(void) const
{
	set<Client*>::iterator	it;
	string					list;

	while (it != this->_clients.end())
		list += string(it != this->_clients.begin(), " ") + (*it)->getNickname();
	return (list);
}

bool	canJoin(Client* client, const string& password = "") const
{
	if (this->hasClient(client))
		return (false);
	if (this->_clients.size() == this->_userLimit)
		return (false);
	if (!this->_password.empty() && this->_password != password)
		return (false);
}
