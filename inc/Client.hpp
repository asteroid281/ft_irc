/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalaz <apalaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/18 13:40:27 by apalaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <set>

using std::string;
using std::set;

class Channel;

class Client
{
	private:
		int			_fd;
		string		_nickname;
		string		_username;
		string		_realname;
		string		_hostname;
		string		_buffer;
		bool		_authenticated;
		bool		_registered;
		set<string>	_channels;
	public:
		Client(int fd);
		~Client();
		// Getters	/ Done!
		bool	isRegistered() const;
		bool	isAuthenticated() const;
		int		getFd() const;
		const string&	getNickname() const;
		const string&	getUsername() const;
		const string&	getRealname() const;
		const string&	getHostname() const;
		const string&	getBuffer() const;
		const std::set<string>&	getChannels() const;
		// Setters
		void	setNickname(const string& nickname);
		void	setUsername(const string& username);
		void	setRealname(const string& realname);
		void	setHostname(const string& hostname);
		void	setAuthenticated(bool auth);
		void	setRegistered(bool reg);
		// Buffer management
		string	extractMessage();
		void	appendToBuffer(const string& data);
		void	clearBuffer();
		// Channel management
		void	joinChannel(const string& channelName);
		void	leaveChannel(const string& channelName);
		bool	isInChannel(const string& channelName) const;
		// Utility
		string	getPrefix() const;
		string	getFullName() const;
};

#endif
