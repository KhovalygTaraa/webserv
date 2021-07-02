/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 16:28:00 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/26 16:28:01 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executor.hpp"

/*
 * 1) Получение данных
 * 2) Вычленение и парсинг первых двух полей хедера (method-uri, host:port)
 * 3) Считывание всего хедера и его парсинг
 * 4) Ищем нужный Location
 * 5) Выполняем метод
 * 6) Формируем ответ
 * 7) Отправляем ответ
 */

Executor::Executor(Config &configParser, RequestParser &requestParser):
_configParser(configParser),  _requestParser(requestParser) {
	_header_size = 0;
	_error = 0;
//	_max_body_size = _configParser
}

/*
 * first_step - is reading of first two header fields
 * second_step - is reading of all header, this is last step.
 */

bool Executor::receiveRequest(pollfd &sock) {
	char						buffer[BUFFER_SIZE];
	int 						size;
	int 						res;
	std::vector<std::string>	splitted_header;
	std::string					tmp;
	std::string 				header;

	_sock = sock;
	while(true) {
		size = recv(sock.fd, &buffer, BUFFER_SIZE - 1, 0);
		if (size > 0) {
			buffer[size] = '\0';
			tmp.append(buffer);
			res = tmp.find("\r\n\r\n");
			if (res == npos) {
				_header_size = _header_size + size;
				if (_header_size >= MAX_HEADER_SIZE)
					_error = 413;
			}
			else
			{
				if (res >= MAX_HEADER_SIZE)
					_error = 413;
				else {

					header = tmp.substr(0, res + 2);
					splitHeader(splitted_header, header);
					_error = _requestParser.parseHeader(splitted_header);
					tmp.erase(0, res + 4);
					_body.write(tmp.data(), tmp.length());
					break ;
				}
			}
		}
		else if (size == -1) // nice, data is good. We can send this to ResponseMaker!!!
			break;
		else if (size == 0){
			_error = 499;
		}
//		else if (size == -1)
//		{
//			if (_error == 0)
//				_error = 500;
//			return (false);
//			//error detected. Server should close connection
//			// types of error. 1) Connection error 2) Wrong http-header 3) Wrong data-size 4) limit 5) ???
//		}
	}

	std::vector<std::string>::iterator it = splitted_header.begin();
	while (it != splitted_header.end())
	{
		std::cout << *it << "|" << std::endl;
		it++;
	}
	std::cout << std::endl;
	return (true);
}

bool Executor::executeMethod() {
	bool res;

	res = false;
	if (_requestParser.getMethod() == "GET")
		res = methodGet();
	else if (_requestParser.getMethod() == "POST")
		res = methodPost();
	else if (_requestParser.getMethod() == "DELETE")
		res = methodDelete();
	return (res);
}

bool Executor::methodDelete() {
	return (false);
}

bool Executor::methodPost() {
	int				size;
	char			buffer[BUFFER_SIZE];
	std::string		remainder;

	selectLocation(_requestParser.getURI());
	std::string boundary = _requestParser.getBoundary();

	while (1)
	{
		size = recv(_sock.fd, &buffer, BUFFER_SIZE - 1, 0);
		if (size > 0)
		{

		}
		else if (size == 0)
		{
			break ;
		}
		std::ofstream new_file();
	}


	return (false);
}

bool Executor::methodGet() {
	return (false);
}

Executor::Location Executor::selectLocation(std::string uri)
{
	Location location(_configParser.getHosts().front().getLocations().front());
	return (location);
}


int Executor::getError() {
	return (_error);
}

bool Executor::splitHeader(std::vector<std::string> &main_strings, std::string &tmp) {
	size_t 		res;
	static int 	strings_count;
	bool 		next_step;

	while (res != npos) {
		next_step = false;
		//// ищем позицию CRLF || CR || LF
		res = tmp.find("\r\n");
		if (res == npos)
			res = tmp.find('\r');
		if (res == npos)
			res = tmp.find('\n');
		if (res != npos)
			next_step = true;

		//// Игнорируем пустые строки до запроса
		if (next_step && res == 0) {
			if (tmp[0] == '\r' && tmp[1] == '\n')
				tmp.erase(0, 2);
			else
				tmp.erase(0, 1);
			next_step = false;
		}
		//// нашли, добавляем в вектор "main_strings" и удаляем из строки "tmp"
		if (next_step) {
			main_strings.push_back(tmp.substr(0, res));
			if (tmp[res] == '\r' && tmp[res + 1] == '\n')
				tmp.erase(0, res + 2);
			else
				tmp.erase(0, res + 1);
		}
	}

	return (true);
}


bool Executor::sendResponse(pollfd &sock) {
	std::string 		response2;
	std::string 		method;
	std::ifstream		fin;
	std::stringstream	content;
	std::stringstream	content2;
	std::stringstream	response;

	char c;
	int fd;
	int s;

	_data = "HELLO";
	fd = open("root/index.html", O_RDONLY);
//	fcntl(fd, F_SETFL, O_NONBLOCK);
//	if (!fin.is_open())
//		throw "file";
	while ((s = read(fd, &c, 1)) > 0) {
		content2.write(&c, 1);
	}
//	content << "<title>Test C++ HTTP Server</title>\n"
//			<< "<h1>Test Server!</h1>\n"
//			<< "<p>This is body of the test page...</p>\n"
//			<< "<h2>Request headers</h2>\n"
//			<< "<pre>" << _data << "</pre>\n"
//			<< "<em><small>Test C++ Http Server</small></em>\n";
//			<< content2 << "\n";
//	content << content2;

//	std::cout << "Hello " << content2.str().length() << std::endl;
	// Формируем весь ответ вместе с заголовками
	response << "HTTP/1.1 200 OK\r\n"
			 << "Version: HTTP/1.1\r\n"
			 << "Content-Type: text/html\r\n"
			 << "Connection: keep-alive\r\n"
			 << "Content-Length: " << content2.str().length()
			 //			 << "Transfer-Encoding: chunked"
			 << "\r\n\r\n"
			 //			 << "5059\r\n"
			 << content2.str();
//			 << "0" << "\r\n\r\n";
	response2 = response.str();
	if (send(sock.fd, response2.c_str(), response2.length(), 0) < 0)
		throw "over";
	return (true);
}
