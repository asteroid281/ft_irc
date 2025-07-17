/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/17 22:27:50 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>
#include <map>

using std::string;
using std::set;

class Client;

class Channel {
private:
    string _name;
    string _topic;
    string _password;
    set<Client*> _clients;
    set<Client*> _operators;
    set<string> _invitedClients;
    
    // Channel modes
    bool _inviteOnly;
    bool _topicRestricted;
    bool _hasPassword;
    int _userLimit;
    
public:
    Channel(const string& name);
    ~Channel();
    
    // Getters
    const string& getName() const;
    const string& getTopic() const;
    const string& getPassword() const;
    const set<Client*>& getClients() const;
    const set<Client*>& getOperators() const;
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    bool hasPassword() const;
    int getUserLimit() const;
    size_t getClientCount() const;
    
    // Setters
    void setTopic(const string& topic);
    void setPassword(const string& password);
    void setInviteOnly(bool inviteOnly);
    void setTopicRestricted(bool restricted);
    void setUserLimit(int limit);
    
    // Client management
    void addClient(Client* client);
    void removeClient(Client* client);
    bool hasClient(Client* client) const;
    bool hasClient(const string& nickname) const;
    
    // Operator management
    void addOperator(Client* client);
    void removeOperator(Client* client);
    bool isOperator(Client* client) const;
    
    // Invite management
    void inviteClient(const string& nickname);
    void removeInvite(const string& nickname);
    bool isInvited(const string& nickname) const;
    
    // Broadcasting
    void broadcast(const string& message, Client* sender = NULL);
    
    // Utility
    string getModeString() const;
    string getClientList() const;
    bool isEmpty() const;
    bool canJoin(Client* client, const string& password = "") const;
};

#endif
