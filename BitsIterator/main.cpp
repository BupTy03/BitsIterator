#include "IstreamBitsIterator.hpp"
#include "OstreamBitsIterator.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

int main()
{
	std::ifstream ifs("D:\\USER\\Documents\\text.txt", std::ios::in | std::ios::binary);
	if (!ifs) {
		std::cout << "Unable to open file!\n";
		return -1;
	};

	/*std::cout << "'";
	std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::ostream_iterator<char>(std::cout));
	std::cout << "'" << std::endl;*/

	IstreamBitsIterator it(ifs);
	int index = 0;
	while (!it.isLastByte()) {
		if (index % 8 == 0) {
			std::cout << "'";
		}
		std::cout << *it;
		++it;
		++index;
	}

	/*std::for_each(IstreamBitsIterator(ifs), IstreamBitsIterator(), [](const bool currBit) {
		std::cout << currBit;
	});
	std::cout << std::endl;*/

#if 0
	bool arr[]{ 0,1,0,0,1,0,0,0, 0,1,1,0,0,1,0,1, 0,1,1,0,1,1,0,0, 0,1,1,0,1,1,0,0, 0,1,1,0,1,1,1,1, 0,0,1,0,1,1,0,0, 0,0,1,0,0,0,0,0,
		0,1,1,1,0,1,1,1, 0,1,1,0,1,1,1,1, 0,1,1,1,0,0,1,0, 0,1,1,0,1,1,0,0, 0,1,1,0,0,1,0,0, 0,0,1,0,0,0,0,1 };
	std::cout << "'";
	OstreamBitsIterator it(std::cout);
	std::copy(std::cbegin(arr), std::cend(arr), it);
	flush(it);
	std::cout << "'\n";

#endif

	return 0;
}