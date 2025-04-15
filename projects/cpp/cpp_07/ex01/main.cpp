#include "iter.hpp"

template<typename T>
void printElement(T const & elem) 
{
	std::cout << elem << std::endl;
}

template<typename T>
void PrintElementOther(T const & elem) 
{
	std::cout << "Print in other function: " << elem << std::endl;
}

int main(void)
{
	int arr[] = {1, 2, 3, 4, 5};
	std::string strs[] = {"apple", "banana", "cherry"};

	::iter(arr, 5, &printElement<int>);
	::iter(strs, 3, &printElement<std::string>);

	::iter(arr, 5, &PrintElementOther<int>);
	::iter(strs, 3, &PrintElementOther<std::string>);
	return 0;
}