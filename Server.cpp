/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:41:58 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/06 14:41:59 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(char *config) {
//	struct sockaddr *base;
//	int opt;
	CParser(config);

//	this->_lsocket = socket(PF_INET, SOCK_STREAM, 0);
//	if (_lsocket == -1)
//		throw std::strerror(errno);
//	fcntl(_lsocket, F_SETFL, O_NONBLOCK);
//	setsockopt(_lsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
//
//	_base.sin_family = PF_INET;
//	_base.sin_port = htons(port);
//	_base.sin_addr.s_addr = inet_addr(ip.c_str());
//
//	base = reinterpret_cast<struct sockaddr*>(&_base);
//	if (bind(_lsocket, base, sizeof(_base)) == -1)
//		throw std::strerror(errno);
//	if (listen(_lsocket, max_queue) == -1)
//		throw std::strerror(errno);
//
//	fds = new pollfd[2];
//	fds[0].fd = _lsocket;
//	fds[0].events = POLLIN;
//	fds[1] = NULL;
}

//Server::~Server() {
//
//}
//
void Server::start() {
//	int new_client;
//	struct sockaddr_in base;
//	socklen_t len;
//
//	nfds_t size;
//
//	size = _lsocket;
//	std::string rec;
//	char buffer[1024];
//	ssize_t check;

//	while(1) {
//		poll(&fds, size + 1, 0);
//		FD_ZERO(&fds);
//		len = sizeof(base);
//		new_client = accept(_lsocket, reinterpret_cast<struct sockaddr *>(&base), &len);
//		if (new_client == -1)
//			throw std::strerror(errno);
//	}
//	check = recv(new_client, &buffer, 1024, 0);
//	if (check == -1)
//		throw "какая-то ошибка от recv";
//	else if (check == 0)
//		throw "Клиент сбросил соединение";
////	rec[check] = '\0';
//	std::cout << buffer;
//
//	rec = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 20\n\nMessage from server!";
//	send(new_client, rec.c_str(), rec.length(), 0);

}
//
//void Server::addSocket(int sock, short event) {
//	for(int i = 0; fds[i] != NULL; i++)
//	{
//		if (fds[i].events == 0)
//		{
//			fds[i].fd = sock;
//			fds[i].events = event;
//		}
//	}
//}