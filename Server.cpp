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
	struct sockaddr *base;
	int opt;
	int sock;
	struct sockaddr_in	inet;
	this->fds_size = 0;
	fds = new pollfd[2];
	fds[0] = NULL;
	fds[1] = NULL;

	Parser parser(config);
	std::vector<Address> listen = parser.getListen();

	std::cout << "\e[1;32m Listening -> \e[0m";
	for (std::vector<Address>::iterator it = listen.begin(); it != listen.end(); it++) {

		sock = socket(PF_INET, SOCK_STREAM, 0));
		if (sock == -1)
			throw std::strerror(errno);
		fcntl(sock, F_SETFL, O_NONBLOCK);
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		inet.sin_family = PF_INET;
		inet.sin_port = htons(*it->port);
		inet.sin_addr.s_addr = inet_addr(*it->ip.c_str());

		base = reinterpret_cast<struct sockaddr *>(&inet);
		if (bind(sock, base, sizeof(inet)) == -1)
			throw std::strerror(errno);
		if (listen(sock, 5) == -1)
			throw std::strerror(errno);

		addSocket(sock, POLLIN);
	}
	std::cout << "\e[1;32m[OK]\e[0m" << std::endl;
}

Server::~Server() {

}

void Server::start() {
	int new_client;
	struct sockaddr_in base;
	socklen_t len;

	nfds_t size;

	size = _lsocket;
	std::string rec;
	char buffer[1024];
	ssize_t check;

	while(1) {
		poll(&fds, size + 1, 0);
		FD_ZERO(&fds);
		len = sizeof(base);
		new_client = accept(_lsocket, reinterpret_cast<struct sockaddr *>(&base), &len);
		if (new_client == -1)
			throw std::strerror(errno);
	}
	check = recv(new_client, &buffer, 1024, 0);
	if (check == -1)
		throw "какая-то ошибка от recv";
	else if (check == 0)
		throw "Клиент сбросил соединение";
//	rec[check] = '\0';
	std::cout << buffer;

	rec = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 20\n\nMessage from server!";
	send(new_client, rec.c_str(), rec.length(), 0);

}

void Server::addSocket(int sock, short event) {
	int i;

	for(i = 0; fds[i] != NULL; i++)
	{
		if (fds[i].fd == -1)
		{
			fds[i].fd = sock;
			fds[i].events = event;
			return ;
		}
	}
	expandPoll();
	addSocket(sock, event);
}

void Server::expandPoll() {
	pollfd	*tmp;
	int 	i;

	fds_size += 100;
	tmp = new pollfd[fds_size];
	tmp[fds_size - 1] = NULL;
	for(i = 0; fds[i] != NULL; i++)
	{
		tmp[i] = fds[i];
	}
	for(int a = i; tmp[a] != NULL; a++)
	{
		tmp[a].fd = -1;
	}
	delete fds[];
	fds = tmp;
}