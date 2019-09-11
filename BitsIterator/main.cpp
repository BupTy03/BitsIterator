#include "IstreamBitsIterator.hpp"
#include "OstreamBitsIterator.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

int main()
{
#if 0
	std::ifstream ifs("D:\\USER\\Documents\\text.txt", std::ios::in | std::ios::binary);
	if (!ifs) {
		std::cout << "Unable to open file!\n";
		return -1;
	};

	std::for_each(IstreamBitsIterator(ifs), IstreamBitsIterator(), [](const bool currBit) {
		std::cout << currBit;
	});
	std::cout << std::endl;
#endif

	bool arr[]{ 0,1,0,0,1,0,0,0, 0,1,1,0,0,1,0,1, 0,1,1,0,1,1,0,0, 0,1,1,0,1,1,0,0, 0,1,1,0,1,1,1,1, 0,0,1,0,1,1,0,0, 0,0,1,0,0,0,0,0,
		0,1,1,1,0,1,1,1, 0,1,1,0,1,1,1,1, 0,1,1,1,0,0,1,0, 0,1,1,0,1,1,0,0, 0,1,1,0,0,1,0,0, 0,0,1,0,0,0,0,1 };
	std::cout << "'";
	OstreamBitsIterator it(std::cout);
	std::copy(std::cbegin(arr), std::cend(arr), it);
	it.flush();
	std::cout << "'\n";

	return 0;
}