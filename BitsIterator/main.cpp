#include "IstreamBitsIterator.hpp"

#include <string>
#include <fstream>
#include <algorithm>

int main()
{
	std::ifstream ifs("D:\\USER\\Documents\\text.txt", std::ios::in | std::ios::binary);
	if (!ifs) {
		std::cout << "Unable to open file!\n";
		return -1;
	}
	;
	std::for_each(IstreamBitsIterator(ifs), IstreamBitsIterator(), [](const bool currBit) {
		std::cout << currBit;
	});
	std::cout << std::endl;

	return 0;
}