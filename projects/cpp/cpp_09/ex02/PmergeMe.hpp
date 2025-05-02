/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmychaly <mmychaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 02:25:20 by mmychaly          #+#    #+#             */
/*   Updated: 2025/05/03 01:05:43 by mmychaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <climits>
#include <cerrno>

class PmergeMe
{
	public:
		PmergeMe(void);
		PmergeMe(PmergeMe const & src);
		PmergeMe & operator=(PmergeMe const & src);
		~PmergeMe(void);

		bool checkFillDataVec(int argc, char** argv);
		void sortVector(void);
		std::vector<int> fordJohnsonVec(std::vector<int> & data);
		int insertBinaryVec(std::vector<int> & data, int numb);
		size_t getVecsize(void);
		void getSortedDataVector(void);
		
		bool checkFillDataList(int argc, char** argv);
		void sortList(void);
		std::list<int> fordJohnsonList(std::list<int> & data);
		int insertBinarylist(std::list<int> & data, int numb);
		size_t getListsize(void);
		void getSortedDataList(void);
		
		void getInitialData(int argc, char** argv);
		
	private:
		std::vector<int> _dataVec;
		std::list<int> _dataList;
};

#endif