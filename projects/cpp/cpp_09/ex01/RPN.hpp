/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:03:54 by mmychaly          #+#    #+#             */
/*   Updated: 2025/04/28 21:03:55 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <exception>

class RPN
{
	public:
		RPN(void);
		RPN(RPN const & src);
		RPN & operator=(RPN const & src);
		~RPN(void);

		bool checkData(const std::string & data);
		void executeRPN(const std::string & data);

	private:
		std::stack<int> _data;
};

#endif