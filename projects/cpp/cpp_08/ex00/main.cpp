#include "easyfind.hpp"


int main(void)
{
	std::cout << "Test vector with easyfind" << std::endl;
	std::vector<int> x;
	x.push_back(7);
	x.push_back(5);
	x.push_back(16);
	x.push_back(1);
	x.push_back(30);
	x.push_back(1);

	std::vector<int>::const_iterator itVec;
	try
	{
		itVec = easyfind<std::vector<int> >(x, 1);
		std::cout << "Value find in vector is: " << *itVec << std::endl;
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Test list with easyfind" << std::endl;
	std::list<int> y;
	y.push_back(10);
	y.push_back(2);
	y.push_back(88);
	y.push_back(1);
	y.push_back(30);
	y.push_back(50);

	std::list<int>::const_iterator itList;
	try
	{

		itList = easyfind<std::list<int> >(y, 50);
		std::cout << "Value find in list is: " << *itList << std::endl;
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Test with value inexistent" << std::endl;
	std::vector<int> g;
	g.push_back(3);
	g.push_back(0);
	g.push_back(56);


	std::vector<int>::const_iterator itVecG;
	try
	{
		itVecG = easyfind<std::vector<int> >(g, 2);
		std::cout << "Value find in vector is: " << *itVecG << std::endl;
	}
	catch(const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}