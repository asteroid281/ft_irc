/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/18 13:45:15 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include <map>

using std::string;
using std::set;

class Client;

class Channel
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
		// Getters	/ Done!
		size_t	getClientCount() const;
		bool	isInviteOnly() const;
		bool	isTopicRestricted() const;
		bool	hasPassword() const;
		int		getUserLimit() const;
		const string&	getName() const;
		const string&	getTopic() const;
		const string&	getPassword() const;
		const set<Client*>&	getClients() const;
		const set<Client*>&	getOperators() const;
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
		string	getModeString() const;
		string	getClientList() const;
		bool	isEmpty() const;
		bool	canJoin(Client* client, const string& password = "") const;
};

#endif
