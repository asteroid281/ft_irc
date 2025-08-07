#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <string>
# include <set>
# include <map>

using	std::string;
using	std::set;

class	Client;

class	Channel
{
	private:
		set<Client*>	_clients;
		set<Client*>	_operators;
		set<string>		_invitedClients;
		string	_name;
		string	_topic;
		string	_password;
		// Channel modes
		bool	_inviteOnly;
		bool	_topicRestricted;
		bool	_hasPassword;
		int		_userLimit;
	public:
		Channel(const string& name);
		~Channel();
		// Getters
		size_t	getClientCount(void) const;
		bool	isInviteOnly(void) const;
		bool	isTopicRestricted(void) const;
		bool	hasPassword(void) const;
		int		getUserLimit(void) const;
		const string&	getName(void) const;
		const string&	getTopic(void) const;
		const string&	getPassword(void) const;
		const set<Client*>&	getClients(void) const;
		const set<Client*>&	getOperators(void) const;
		// Setters
		void	setTopic(const string& topic);
		void	setPassword(const string& password);
		void	setInviteOnly(bool inviteOnly);
		void	setTopicRestricted(bool restricted);
		void	setUserLimit(int limit);
		// Client management
		void	addClient(Client* client);
		void	removeClient(Client* client);
		bool	hasClient(Client* client) const;
		bool	hasClient(const string& nickname) const;
		// Operator management
		void	addOperator(Client* client);
		void	removeOperator(Client* client);
		bool	isOperator(Client* client) const;
		// Invite management
		void	inviteClient(const string& nickname);
		void	removeInvite(const string& nickname);
		bool	isInvited(const string& nickname) const;
		// Broadcasting
		void	broadcast(const string& message, Client* sender = NULL);
		// Utility
		string	getModeString(void) const;
		string	getClientList(void) const;
		bool	isEmpty(void) const;
		bool	canJoin(Client* client, const string& password = "") const;
};

#endif
