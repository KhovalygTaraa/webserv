# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swquinc <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 20:37:17 by swquinc           #+#    #+#              #
#    Updated: 2021/06/17 20:37:19 by swquinc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wserver

PARSER		=	CParser.cpp RequestParser.cpp CParser.hpp RequestParser.hpp
CORE		=	Server.cpp Server.hpp
RESPONSE	=	ResponseMaker.cpp ResponseMaker.hpp
MAIN		=	webserv.cpp

PARSERRDIR	=	parser/
COREDIR		=	core/
RESPONSEDIR	=	response/
OBJDIR		=	objs/

FILES		=	$(addprefix $(PARSERRDIR), $(PARSER)) \
				$(addprefix $(COREDIR), $(CORE)) \
				$(addprefix $(RESPONSEDIR), $(RESPONSE))

CPP			=	$(filter %.cpp, $(FILES)) $(MAIN)
OBJS		=	$(patsubst %.cpp,%.o,$(CPP)) # another way $($(CPP):.cpp=.o)
HPP			=	$(addprefix -I , $(filter %.hpp, $(FILES)))
$(warning $(OBJS))


all:
	clang++ -Wall -Wextra -Werror $(CPP) $(HPP) -o $(NAME)

clean:

fclean: clean

re: fclean all
