/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 19:16:07 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/08 18:48:06 by swquinc          ###   ########.fr       */
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
	while (str[i] != '\0')
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
	while (str[i] != '\0')
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
	int	i;
	int stdin1;

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
		system_error("socket error");
	a.sin_family = PF_INET;
//	strlcpy(a.sun_path, "h1.sock", 8);
	a.sin_port = htons(80);
	a.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr*)&a, sizeof(a)) == -1)
		system_error("bind error");
	if (listen(sock, 5) == -1)
		system_error("listen error");
	slen = sizeof(a);
	if ((new_socket = accept(sock, (struct sockaddr*)&a, &slen)) == -1)
		system_error("accept error");
//	ft_putendl_fd(new_socket, "Привет клиент!");
/*	if (fork() == 0)
	{
		char *str;
		while (1)
		{
			get_next_line(new_socket, &str);
			ft_putstr_fd(1, "Client: ");
			ft_putstr_fd(1, str);
			if (strcmp("EXIT", str) == 0)
				break ;
		}
		exit(1);
	}*/
	while (1)
	{
		ft_putstr_fd(1, "Server: ");
		get_next_line(0, &c);
		ft_putendl_fd(new_socket, c);
		if (strcmp("EXIT", c) == 0)
			break ;
		get_next_line(new_socket, &c);
		ft_putstr_fd(1, "Client: ");
		ft_putendl_fd(1, c);
	}
	printf("Остановка сервера...\n");
	i = 3;
	while (i != 0)
	{
		printf("%d\n", i);
		sleep(1);
		i--;
	}
	close(new_socket);
	close(sock);
	unlink("h1.sock");
	return (0);
}
