#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <vector>

// IRC Reply codes
#define RPL_WELCOME 001
#define RPL_YOURHOST 002
#define RPL_CREATED 003
#define RPL_MYINFO 004
#define RPL_TOPIC 332
#define RPL_NAMREPLY 353
#define RPL_ENDOFNAMES 366
#define RPL_LIST 322
#define RPL_LISTEND 323
#define RPL_CHANNELMODEIS 324
#define RPL_NOTOPIC 331
#define RPL_WHOREPLY 352
#define RPL_ENDOFWHO 315
#define RPL_WHOISUSER 311
#define RPL_ENDOFWHOIS 318

// IRC Error codes
#define ERR_NOSUCHNICK 401
#define ERR_NOSUCHCHANNEL 403
#define ERR_CANNOTSENDTOCHAN 404
#define ERR_NOTONCHANNEL 442
#define ERR_USERONCHANNEL 443
#define ERR_NOTREGISTERED 451
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTRED 462
#define ERR_PASSWDMISMATCH 464
#define ERR_CHANNELISFULL 471
#define ERR_INVITEONLYCHAN 473
#define ERR_BADCHANNELKEY 475
#define ERR_CHANOPRIVSNEEDED 482
#define ERR_NICKNAMEINUSE 433
#define ERR_ERRONEUSNICKNAME 432

using std::vector;
using std::string;

class Server;
class Client;

class Commands
{
	private:
		Server* _server;
	public:
		Commands(Server* server);
		~Commands();
		void	processCommand(Client* client, const string& command);
		// Authentication commands
		void	cmdPass(Client* client, const vector<string>& params);
		void	cmdNick(Client* client, const vector<string>& params);
		void	cmdUser(Client* client, const vector<string>& params);
		// Channel commands
		void	cmdJoin(Client* client, const vector<string>& params);
		void	cmdPart(Client* client, const vector<string>& params);
		void	cmdTopic(Client* client, const vector<string>& params);
		void	cmdNames(Client* client, const vector<string>& params);
		void	cmdList(Client* client, const vector<string>& params);
		// Communication commands
		void	cmdPrivmsg(Client* client, const vector<string>& params);
		void	cmdNotice(Client* client, const vector<string>& params);
		// Channel operator commands
		void	cmdKick(Client* client, const vector<string>& params);
		void	cmdInvite(Client* client, const vector<string>& params);
		void	cmdMode(Client* client, const vector<string>& params);
		// Server commands
		void	cmdPing(Client* client, const vector<string>& params);
		void	cmdPong(Client* client, const vector<string>& params);
		void	cmdQuit(Client* client, const vector<string>& params);
		void	cmdWho(Client* client, const vector<string>& params);
		void	cmdWhois(Client* client, const vector<string>& params);
		// Utility
		vector<string>	parseParams(const string& command);
		void			sendWelcome(Client* client);
		void			sendError(Client* client, const string& error);
};

#endif
