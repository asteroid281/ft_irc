/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunozdem < yunozdem@student.42istanbul.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/07/17 22:32:21 by yunozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using std::string;
using std::vector;

class Utils {
public:
    static vector<string> split(const string& str, char delimiter);
    static string trim(const string& str);
    static string toUpper(const string& str);
    static string toLower(const string& str);
    static bool isValidChannelName(const string& name);
    static bool isValidNickname(const string& nickname);
    static string getCurrentTime();
    static string formatMessage(int code, const string& target, const string& message);
    static string joinVector(const vector<string>& vec, const string& delimiter, size_t start = 0);
};

#endif
