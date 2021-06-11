/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CParser.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:48:12 by swquinc           #+#    #+#             */
/*   Updated: 2021/06/06 14:48:14 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPARSER_HPP
# define CPARSER_HPP
# include <iostream>
# include <vector>
# include <string>

/*
 *  config - это путь к конфиг-файлу, относительно нашей программы-сервера. Открываешь, считываешь и парсишь.
 */

class CParser {
	private:
		CParser();
		struct Listen { int port; nstd::string ip; }; // сюда парсишь port и ip.
		std::vector<Listen> listen; // сюда нужно разложить все экземпляры структуры Listen. Дублирования не должно быть.
	public:
		CParser(char *config); // если config == NULL, нужно расспарсить config file по-умолчанию.
		~CParser(); // динамическую память нужно почистить, если она была выделена.
		std::vector<Listen> getListen(void) const;
};

#endif

