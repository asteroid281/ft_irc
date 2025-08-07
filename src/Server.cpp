#include "Server.hpp"

Server::Server(int port, const string& password)
{
	this->_port = port;
	this->_password = password;
	this->_serverSocket = -1;
	this->_running = false;
}

Server::~Server()
{}

const string&	Server::getPassword(void) const
{
	return (this->_password);
}

const string&	Server::getServerName(void) const
{
	return (this->_serverName);
}

const string&	Server::getVersion(void) const
{
	return (this->_version);
}

const string&	Server::getCreationDate(void) const
{
	return (this->_creationDate);
}

Client*	Server::getClient(int fd)
{
	map<int, Client*>::iterator	it;

	it = this->_clients.find(fd);
	if (it != this->_clients.end())
		return (it->second);
	return (nullptr);
}

Client*	Server::getClientByNick(const string& nickname)
{
	map<int, Client*>::iterator	it;

	it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second->getNickname() == nickname)
			return (it->second);
		++it;
	}
	return (nullptr);
}

void Server::removeClient(Client* client)
{
	int fd;

	if (client)
	{
		fd = client->getSocketFd();
		this->_clients.erase(fd);
		close(fd);
		delete (client);
	}
}

Channel*	Server::getChannel(const string& name)
{
	map<string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it != this->_channels.end())
		return (it->second);
	return (nullptr);
}

Channel*	Server::createChannel(const string& name, Client* creator)
{
	Channel*	channel;

	channel = new Channel(name, creator);
	this->_channels[name] = channel;
	return (channel);
}

void	Server::removeChannel(const string& name)
{
	map<string, Channel*>::iterator	it;

	it = this->_channels.find(name);
	if (it != this->_channels.end())
	{
		delete (it->second);
		this->_channels.erase(it);
	}
}

void	Server::broadcastToChannel(const string& channelName, const string& message, Client* sender = NULL)
{
	Channel	*channel;

	channel = this->getChannel(channelName);
	if (channel == nullptr)
		return ;
	channel->broadcast(message, sender);
}

void	Server::sendToClient(int fd, const string& message)
{
	size_t	sent;
	string	part;

	sent = send(fd, message.c_str(), message.length(), 0);
	if (sent == -1)
		return (perror("Error: send"));
	part = message;
	while (sent != part.length())
	{
		sent = send(fd, part.c_str(), part.length(), 0);
		if (sent == -1)
			return (perror("Error: send"));
		part = part.substr(sent);
	}
}

vector<string>	Server::getChannelList(void)
{
	map<string, Channel*>::iterator	it;
	vector<string>					channelList;

	it = this->_channels.begin();
	while (it != this->_channels.end())
	{
		channelList.push_back(it->first);
		++it;
	}
	return (channelList);
}

void	Server::setupSocket(void)
{
	struct sockaddr_in	serverAddr;
	struct pollfd		serverPollFd;
    int					opt;

    this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_serverSocket == -1)
        throw	runtime_error("Server Socket Error.");
	opt = 1;
    if (setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        close(this->_serverSocket);
        throw	runtime_error("Server Socket Options Error.");
    }
    if (fcntl(this->_serverSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        close(this->_serverSocket);
        throw	runtime_error("Server Socket Non-blocking Error.");
    }
    serverAddr = (struct sockaddr_in){0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(this->_port);
    if (bind(this->_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        close(this->_serverSocket);
        throw	runtime_error("Server Socket Bind Error.");
    }
    if (listen(this->_serverSocket, MAX_CLIENTS) == -1)
    {
        close(this->_serverSocket);
        throw	runtime_error("Server Socket Listen Error.");
    }
    serverPollFd.fd = this->_serverSocket;
    serverPollFd.events = POLLIN;
    serverPollFd.revents = 0;
    this->_fds.push_back(serverPollFd);
    cout << "The server started listening on port " << this->_port << endl;
}

void	Server::acceptNewClient(void)
{
    struct sockaddr_in	clientAddr;
    socklen_t			clientLen;
    Client*				newClient;
    struct pollfd		clientPollFd;
    int					clientSocket;

    clientLen = sizeof(clientAddr);
    clientSocket = accept(this->_serverSocket, (struct sockaddr*) &clientAddr, &clientLen);
    if (clientSocket == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return ;
        perror("Client Accept Error");
        return ;
    }
    if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        perror("Client Socket Non-blocking Error");
        close(clientSocket);
        return ;
    }
    newClient = new Client(clientSocket);
    this->_clients[clientSocket] = newClient;
    clientPollFd.fd = clientSocket;
    clientPollFd.events = POLLIN;
    clientPollFd.revents = 0;
    this->_fds.push_back(clientPollFd);
    cout << "New client connected." << endl;
}

void	Server::handleClientMessage(int clientFd)
{
	Client	*client;
	string	buffer;
	char	buff[BUFFER_SIZE];
	size_t	b_read;

	b_read = read(clientFd, buff, BUFFER_SIZE - 1);
	client = this->getClient(clientFd);
	if (b_read <= 0)
		return (this->removeClient(client));
	if (client)
	{
		buffer.assign(buff, b_read);
		client->appendToBuffer(buffer);
		buffer = client->extractMessage();
		while (buffer.length())
		{
			this->processCommand(client, buffer);
			buffer = client->extractMessage();
		}
	}
}

void	Channel::removeClient(int clientFd)
{
	set<Client*>::iterator			s_it;
	vector<struct pollfd>::iterator	v_it;

	s_it = this->_clients.begin();
	while (s_it != this->_clients.end())
	{
		if ((*s_it)->getFd() == clientFd)
		{
			this->_clients.erase(s_it);
			v_it = this->_fds.begin();
			while (v_it != this->_fds.end())
			{
				if (v_it->fd == clientFd)
				{
					this->_fds.erase(v_it);
					return ;
				}
				++v_it;
			}
		}
		++s_it;
	}
}

//	Yorum Satiri Var, Kod Eksik !
void	Server::processCommand(Client* client, const string& message)
{
	Commands		commands;
	void			(*cmd)(Client* client, const vector<string>& params);
	vector<string>	parsedString;
	vector<string>	params;
	string			temp;
	size_t			i;

	i = -1;
	while (message[++i])
	{
		if (message[i] != ' ')
			temp += message[i];
		else if (!temp.empty())
		{
			parsedString.push_back(temp);
			temp.clear();
		}
	}
	params.assign(parsedString.begin() + 1, parserString.end());
	if (parsedString[0] == "PASS")
		cmd = &commands.cmdPass;
	else if (parsedString[0] == "NICK")
		cmd = &commands.cmdNick;
	else if (parsedString[0] == "USER")
		cmd = &commands.cmdUser;
	else if (parsedString[0] == "JOIN")
		cmd = &commands.cmdJoin;
	else if (parsedString[0] == "PART")
		cmd = &commands.cmdPart;
	else if (parsedString[0] == "TOPIC")
		cmd = &commands.cmdTopic;
	else if (parsedString[0] == "NAMES")
		cmd = &commands.cmdNames;
	else if (parsedString[0] == "LIST")
		cmd = &commands.cmdList;
	else if (parsedString[0] == "PRIVMSG")
		cmd = &commands.cmdPrivmsg;
	else if (parsedString[0] == "NOTICE")
		cmd = &commands.cmdNotice;
	else if (parsedString[0] == "KICK")
		cmd = &commands.cmdKick;
	else if (parsedString[0] == "INVITE")
		cmd = &commands.cmdInvite;
	else if (parsedString[0] == "MODE")
		cmd = &commands.cmdMode;
	else if (parsedString[0] == "PING")
		cmd = &commands.cmdPing;
	else if (parsedString[0] == "PONG")
		cmd = &commands.cmdPong;
	else if (parsedString[0] == "QUIT")
		cmd = &commands.cmdQuit;
	else if (parsedString[0] == "WHO")
		cmd = &commands.cmdWho;
	else if (parsedString[0] == "WHOIS")
		cmd = &commands.cmdWhois;
	else
	{
		//	Error
	}
	cmd(client, params);
}
