/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:41:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/06 14:41:53 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP
//# include "webserv.hpp"
# include <stdio.h>
# include <iostream>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/select.h> // select - for non-blocking connection
# include <poll.h> // poll - for non-blocking connection (recommended)
# include <sys/types.h> // kqueue - for non-blocking connection
# include <sys/time.h> // kqueue - for non-blocking connection
# include <sys/un.h>
# include <sys/stat.h>
# include <vector>
# include "CParser.hpp"

class Server {
	public:
		Server(char *config);
		~Server();
		void start();
	private:
		typedef std::vector<Address> Listen;
		void addSocket(int sock, short event);
		void expandPoll();
		std::vector<int>	_lsocket;
		pollfd				*fds;
		int 				fds_size;
};

#endif