/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:27:54 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/26 16:27:55 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
# define EXECUTOR_HPP
# include "ConfigParser.hpp"
# include "RequestParser.hpp"
# include <iostream>
# include <sys/socket.h>
# include <poll.h>
# include <vector>
# include <sstream>
# include <string>
# include <list>
# include <unistd.h>
# include <fcntl.h>
# include <fstream>
# define MAX_HEADER_SIZE 8192

class Executor {
	public:
		Executor(Config &configParser, RequestParser &requestParser);
		bool receiveRequest(pollfd &sock); // header
		bool executeMethod(); // POST GET DELETE
		bool sendResponse(pollfd &sock); // send response

	private:
		typedef Config::Host::Location Location;

		int						_error;
		pollfd					_sock;
		size_t					_max_body_size;
		char					*_data;
		Config					&_configParser;
		RequestParser			&_requestParser;


		size_t 					_content_length; // 0 if absent
		size_t 					_header_size;
		std::stringstream 		_body;

		//add
		bool 		splitHeader(std::vector<std::string> &main_strings, std::string &tmp);
		Location	selectLocation(std::string uri);
		int 		getError();
		//core
		bool 		methodDelete();
		bool 		methodPost();
		bool 		methodGet();
};

#endif
