#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <poll.h>
# include <string>
# include <vector>
# include <set>

using	std::string;
using	std::set;

class	Channel;

class	Client
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
		// Getters
		bool	isRegistered(void) const;
		bool	isAuthenticated(void) const;
		int		getFd(void) const;
		const string&	getNickname(void) const;
		const string&	getUsername(void) const;
		const string&	getRealname(void) const;
		const string&	getHostname(void) const;
		const string&	getBuffer(void) const;
		const std::set<string>&	getChannels(void) const;
		// Setters
		void	setNickname(const string& nickname);
		void	setUsername(const string& username);
		void	setRealname(const string& realname);
		void	setHostname(const string& hostname);
		void	setAuthenticated(bool auth);
		void	setRegistered(bool reg);
		// Buffer management
		string	extractMessage(void);
		void	appendToBuffer(const string& data);
		void	clearBuffer(void);
		// Channel management
		void	joinChannel(const string& channelName);
		void	leaveChannel(const string& channelName);
		bool	isInChannel(const string& channelName) const;
		// Utility
		string	getPrefix(void) const;
		string	getFullName(void) const;
};

#endif
