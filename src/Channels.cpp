#include "Channel.hpp"

// Set default values !!!
Channel::Channel(const string& name)
{}

// Don't forget to check there is a pointer to be deleted !!!
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
