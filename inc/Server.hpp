/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/17 22:32:13 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "Channel.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <csignal>
#include <cstring>

#define MAX_CLIENTS 100
#define BUFFER_SIZE 512

using std::string;
using std::map;
using std::vector;

class Client;
class Channel;

class Server {
private:
    int _port;
    string _password;
    int _serverSocket;
    vector<struct pollfd> _fds;
    map<int, Client*> _clients;
    map<string, Channel*> _channels;
    bool _running;
    string _serverName;
    string _version;
    string _creationDate;

    void _setupSocket();
    void _acceptNewClient();
    void _handleClientMessage(int clientFd);
    void _removeClient(int clientFd);
    void _processCommand(Client* client, const string& message);

public:
    Server(int port, const string& password);
    ~Server();
    
    void start();
    void stop();
    
    // Getters
    const string& getPassword() const;
    const string& getServerName() const;
    const string& getVersion() const;
    const string& getCreationDate() const;
    
    // Client management
    Client* getClient(int fd);
    Client* getClientByNick(const string& nickname);
    void removeClient(Client* client);
    
    // Channel management
    Channel* getChannel(const string& name);
    Channel* createChannel(const string& name, Client* creator);
    void removeChannel(const string& name);
    
    // Message broadcasting
    void broadcastToChannel(const string& channelName, const string& message, Client* sender = NULL);
    void sendToClient(int fd, const string& message);
    
    // Utility
    bool isValidNickname(const string& nickname);
    vector<string> getChannelList();
};

#endif
