#include "Commands.hpp"

Commands::Commands(Server *server)
{
	this->_server = server;
}

Commands::~Commands()
{}

void	Commands::cmdPass(Client* client, const vector<string>& params)
{}

void	Commands::cmdNick(Client* client, const vector<string>& params)
{}

void	Commands::cmdUser(Client* client, const vector<string>& params)
{}

void	Commands::cmdJoin(Client* client, const vector<string>& params)
{}

void	Commands::cmdPart(Client* client, const vector<string>& params)
{}

void	Commands::cmdTopic(Client* client, const vector<string>& params)
{}

void	Commands::cmdNames(Client* client, const vector<string>& params)
{}

void	Commands::cmdList(Client* client, const vector<string>& params)
{}

void	Commands::cmdPrivmsg(Client* client, const vector<string>& params)
{}

void	Commands::cmdNotice(Client* client, const vector<string>& params)
{}

void	Commands::cmdKick(Client* client, const vector<string>& params)
{}

void	Commands::cmdInvite(Client* client, const vector<string>& params)
{}

void	Commands::cmdMode(Client* client, const vector<string>& params)
{}

void	Commands::cmdPing(Client* client, const vector<string>& params)
{}

void	Commands::cmdPong(Client* client, const vector<string>& params)
{}

void	Commands::cmdQuit(Client* client, const vector<string>& params)
{}

void	Commands::cmdWho(Client* client, const vector<string>& params)
{}

void	Commands::cmdWhois(Client* client, const vector<string>& params)
{}

void	Commands::sendWelcome(Client* client)
{}

void	Commands::sendError(Client* client, const string& error)
{}

