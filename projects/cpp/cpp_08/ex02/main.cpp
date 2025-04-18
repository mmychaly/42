#include "MutantStack.hpp"

int main(void)
{
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << "Test copy" << std::endl;
	while (!s.empty())
	{
		std::cout << s.top() << std::endl;
		s.pop();
	}
	std::cout << "Test vector" << std::endl;
	MutantStack<int, std::vector<int> > x;
	x.push(100);
	x.push(0);
	std::cout << "top: " << x.top() << std::endl;
	std::cout << "size: " << x.size() << std::endl;
	std::cout << std::endl;
	x.push(500);
	x.push(100500);
	MutantStack<int, std::vector<int> >::const_iterator itxb = x.begin();
	MutantStack<int, std::vector<int> >::const_iterator itxe = x.end();
	while (itxb != itxe)
	{
		std::cout << *itxb << std::endl;
		++itxb;
	}
	std::cout << "top: " << x.top() << std::endl;
	std::cout << "Test list" << std::endl;
	MutantStack<int, std::vector<int> > y;
	y.push(10);
	y.push(19);
	std::cout << "top: " << y.top() << std::endl;
	std::cout << "size: " << y.size() << std::endl;
	std::cout << std::endl;
	y.push(21);
	y.push(202);
	MutantStack<int, std::vector<int> >::const_iterator ityb = y.begin();
	MutantStack<int, std::vector<int> >::const_iterator itye = y.end();
	while (ityb != itye)
	{
		std::cout << *ityb << std::endl;
		++ityb;
	}
	std::cout << "top: " << y.top() << std::endl;
	return 0;
}