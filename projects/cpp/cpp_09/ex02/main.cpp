#include "PmergeMe.hpp"
#include <ctime>
#include <iomanip>

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "Error: wrong number of arguments!" << std::endl;
		return 1;
	}

	PmergeMe x;

	clock_t startVec = clock();
	if (x.checkFillDataVec(argc, argv))
		x.sortVector();
	else 
		return 1;
	clock_t endVec = clock();
	double timeVec = (double(endVec - startVec) / CLOCKS_PER_SEC) * 1000000;

	std::cout << "Befor: ";
	x.getInitialData(argc, argv);
	std::cout << "After: ";
	x.getSortedDataVector();
	std::cout << "Time to process a range of " << x.getVecsize() << " elements with std::vector : " << timeVec << " us" << std::endl;

	clock_t startList = clock();
	if (x.checkFillDataList(argc, argv))
		x.sortList();
	else 
		return 1;

	clock_t endList = clock();
	double timeList = (double(endList - startList) / CLOCKS_PER_SEC) * 1000000;

	std::cout << "Time to process a range of " << x.getListsize() << " elements with std::list : " << timeList << " us" << std::endl;
	
	return 0;
}