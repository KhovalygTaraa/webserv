/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:16:07 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/06 17:31:58 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	system_error(char *str)
{
	perror(str);
//	write(2, str, strlen(str));
	exit(EXIT_FAILURE);
}

void ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
}

void ft_putendl_fd(int fd, char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		ft_putchar_fd(fd, str[i]);
		i++;
	}
	write(fd, "\n", 1);
}

void ft_putstr_fd(int fd, char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		ft_putchar_fd(fd, str[i]);
		i++;
	}
}

int main(int argc, char **argv)
{
	int sock;
	struct sockaddr_in a;
	char *c;
	int fd;
	int new_socket;
	socklen_t slen;

	if (argc == 1)
	{
		printf("Error: put ip as first argument");
		return (0);
	}
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
		system_error("socket error");
	a.sin_family = PF_INET;
	a.sin_port = htons(1055);
	inet_aton(argv[1], &(a.sin_addr));
//	strlcpy(a.sun_path, "h1.sock", 8);
//	if (bind(sock, (struct sockaddr*)&a, sizeof(a)) == -1)
//		system_error("bind error");
//	if (listen(sock, 5) == -1)
//		system_error("listen error");
//	slen = sizeof(a);
//	if ((new_socket = accept(socket, (struct sockaddr*)&a, slen)) == -1)
//		system_error("accept error");
	if ((new_socket = connect(sock, (struct sockaddr*)&a, sizeof(a))) == -1 )
		system_error("connect error");
//		get_next_line(sock, &c);
//		printf("Server: %s\n", c);
		ft_putendl_fd(1, "Connected!");
/*	if (fork() == 0)
	{
		char *str;

		while (1)
		{
			get_next_line(0, &str);
			ft_putstr_fd(sock, "Client: ");
			ft_putstr_fd(sock, str);
			if (strcmp("EXIT", str) == 0)
				break ;
		}
		exit(1);
	}*/
//	c = NULL;
	while(1)
	{
		get_next_line(sock, &c);
		printf("Server: %s\n", c);
		if (strcmp("EXIT", c) == 0)
			break ;
		ft_putstr_fd(1, "Client: ");
		get_next_line(0, &c);
		ft_putendl_fd(sock, c);
	}
	printf("Сервер закрыл соединение\n");
//	close(new_socket);
//	close(sock);
//	unlink("h1.sock");
	return (0);
}
