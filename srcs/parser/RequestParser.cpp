/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 16:43:18 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/19 16:43:20 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

RequestParser::RequestParser() {

}

RequestParser::RequestParser(Config &configParser): _config(configParser) {
}

RequestParser::~RequestParser() {

}

bool	RequestParser::parseHeader(std::vector<std::string> &header) {
	int a;

	if (header.front().find("GET"))
		_method = "GET";
	else if (header.front().find("POST"))
		_method = "POST";
	for(int i = 0; header[i] != header.back(); i++)
	{
		a = header[i].find("boundary");
		if (a)
		{
			_boundary = header[i].substr(a + 8, header[i].length() - (a + 8));
		}
	}
	return (true);
}

std::string		RequestParser::getBoundary() const {
	return (_boundary);
}

std::string		RequestParser::getMethod() const {
	return (_method);
}

std::string 	RequestParser::getURI() const {
	return ("/");
}

std::string 	RequestParser::getContentType() const {
	return ("multipart/form-data");
}

int 			RequestParser::getError() const {
	return (400);
}

size_t			RequestParser::getContentLength() const {
	return (_content_length);
}

RequestParser&	RequestParser::operator=(const RequestParser &r) {
	return (*this);
}
