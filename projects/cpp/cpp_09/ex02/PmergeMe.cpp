#include "PmergeMe.hpp"


PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(PmergeMe const & src)
{
	*this = src;
}

PmergeMe & PmergeMe::operator=(PmergeMe const & src)
{
	if (this != &src)
	{
		_dataVec = src._dataVec;
		_dataList = src._dataList;
	}
	return *this;
}

PmergeMe::~PmergeMe(void) {}

int PmergeMe::insertBinaryVec(std::vector<int> & data, int numb)
{
	int pos = 0;
	int len = data.size();
	while (pos < len)
	{
		int mid = (pos + len) / 2;
		if (data[mid] < numb)
			pos = mid + 1;
		else
			len = mid;
	}
	return pos;
}

std::vector<int> PmergeMe::fordJohnsonVec(std::vector<int> & data)
{
	if (data.size() == 1)
		return data;
	else if (data.size() == 2)
	{
		if (data[0] > data[1])
			std::swap(data[0], data[1]);
		return data;
	}
	std::vector<int> leaders;
	std::vector<int> followers;
	for (size_t i = 0; i+1 < data.size(); i += 2)
	{
		if (data[i] < data[i+1])
		{
			followers.push_back(data[i]);
			leaders.push_back(data[i+1]);
		}
		else
		{
			followers.push_back(data[i+1]);
			leaders.push_back(data[i]);
		}
	}
	if (data.size() % 2)
		followers.push_back(data.back());

	std::vector<int> sorted = fordJohnsonVec(leaders);

	for (std::vector<int>::reverse_iterator rit = followers.rbegin(); rit != followers.rend(); rit++ )
	{
		int pos = insertBinaryVec(sorted, *rit);
		sorted.insert(sorted.begin() + pos, *rit);
	}
	return sorted;
}

int PmergeMe::insertBinarylist(std::list<int> & data, int numb)
{
	int pos = 0;
	int len = data.size();
	std::list<int>::iterator it;
	while (pos < len)
	{
		int mid = (pos + len) / 2;
		it = data.begin();
		std::advance(it, mid);
		if (*it < numb)
			pos = mid + 1;
		else
			len = mid;
	}
	return pos;
}
std::list<int> PmergeMe::fordJohnsonList(std::list<int> & data)
{
	if (data.size() == 1)
		return data;
	std::list<int>::iterator it = data.begin();
	std::list<int>::iterator it_2 = data.begin();
	it_2++;
	if (data.size() == 2)
	{
		if (*it > *it_2)
			std::iter_swap(it, it_2);
		return data;
	}
	std::list<int> leaders;
	std::list<int> followers;
	it = data.begin();
	it_2 = data.begin();
	it_2++;
	for (size_t i = 0; i+1 < data.size(); i += 2)
	{
		if (*it < *it_2)
		{
			followers.push_back(*it);
			leaders.push_back(*it_2);
		}
		else
		{
			followers.push_back(*it_2);
			leaders.push_back(*it);
		}
		std::advance(it, 2);
		std::advance(it_2, 2);
	}
	if (data.size() % 2)
		followers.push_back(data.back());

	std::list<int> sorted = fordJohnsonList(leaders);

	for (std::list<int>::reverse_iterator rit = followers.rbegin(); rit != followers.rend(); rit++)
	{
		int pos = insertBinarylist(sorted, *rit);
		std::list<int>::iterator inserPos = sorted.begin();
		std::advance(inserPos, pos);
		sorted.insert(inserPos, *rit);
	}
	return sorted;
}

void PmergeMe::sortVector(void)
{
	std::vector<int> sorted = fordJohnsonVec(_dataVec);
	_dataVec = sorted;
}

void PmergeMe::sortList(void)
{
	std::list<int> sorted = fordJohnsonList(_dataList);
	_dataList = sorted;
}

bool PmergeMe::checkFillDataVec(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		char *end;
		errno = 0;
		long numb = std::strtol(argv[i], &end, 10);
		if (errno == ERANGE || numb > INT_MAX || numb < INT_MIN)
		{
			std::cerr << "Error: bad input => " << argv[i] << std::endl;
			return false;
		}
		if (errno != 0 || *end != '\0')
		{
			std::cerr << "Error: bad input => " << argv[i] << std::endl;
			return false;
		}
		if (numb < 0)
		{
			std::cerr << "Error: only positiv number => " << numb << std::endl;
			return false;
		}
		_dataVec.push_back(static_cast<int>(numb));
	}
	for (size_t i = 0; i < _dataVec.size(); i++)
	{
		for (size_t j = i + 1; j < _dataVec.size();)
		{
			if (_dataVec[i] == _dataVec[j])
				_dataVec.erase(_dataVec.begin() + j);
			else
				j++;
		}
	}
	return true;
}

bool PmergeMe::checkFillDataList(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		char *end;
		errno = 0;
		long numb = std::strtol(argv[i], &end, 10);
		if (errno == ERANGE || numb > INT_MAX || numb < INT_MIN)
		{
			std::cerr << "Error: bad input => " << argv[i] << std::endl;
			return false;
		}
		if (errno != 0 || *end != '\0')
		{
			std::cerr << "Error: bad input => " << argv[i] << std::endl;
			return false;
		}
		if (numb < 0)
		{
			std::cerr << "Error: only positiv number => " << numb << std::endl;
			return false;
		}
		
		_dataList.push_back(static_cast<int>(numb));
	}

	for (std::list<int>::iterator it = _dataList.begin(); it != _dataList.end(); it++)
	{
		std::list<int>::iterator it_2 = it;
		it_2++;
		while (it_2 != _dataList.end())
		{
			if (*it == *it_2)
				it_2 = _dataList.erase(it_2);
			else
				it_2++;
		}
	}
	return true;
}

size_t PmergeMe::getVecsize(void)
{
	return this->_dataVec.size();
}

size_t PmergeMe::getListsize(void)
{
	return this->_dataList.size();
}

void PmergeMe::getSortedDataVector(void)
{
	std::vector<int>::iterator last = _dataVec.end();
	if (!_dataVec.empty())
		last--;
	for (std::vector<int>::iterator it = _dataVec.begin(); it != _dataVec.end(); it++)
	{
		std::cout << *it;
		if (it != last)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::getSortedDataList(void)
{
	std::list<int>::iterator last = _dataList.end();
	if (!_dataList.empty())
		last--;
	for (std::list<int>::iterator it = _dataList.begin(); it != _dataList.end(); it++)
	{

		std::cout << *it;
		if (it != last)
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::getInitialData(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::cout << argv[i];
		if (i != (argc - 1))
			std::cout << " ";
	}
	std::cout << std::endl;
}