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

NAME		=	server

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

OBJS_TMP	=	$(notdir $(patsubst %.cpp,%.o,$(CPP)))

CPP			=	$(filter %.cpp, $(FILES)) $(MAIN)
HPP			=	$(addprefix -I , $(filter %.hpp, $(FILES)))
OBJ			=	$(addprefix $(OBJDIR), $(OBJS_TMP))


all: $(NAME)

$(OBJS): $(CPP)
	mkdir $(OBJDIR)
	clang++	-Wall -Wextra -Werror -c $(CPP) $(HPP)
	mv $(OBJS) $(OBJDIR)

$(NAME): $(OBJ)
	clang++ -Wall -Wextra -Werror -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm $(NAME)

re: fclean all
