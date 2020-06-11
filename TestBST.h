#ifndef TEST_BST_H
#define TEST_BST_H

#include "BST.h"
#include <ctime>
#include <iostream>

namespace testBST
{
	void testPrimes(const int count_elems)
	{
		time_t time = clock();
		std::vector<int> vec = primesVector(count_elems);
		std::cout << "Generating vector of primes in range [2, " << count_elems << "] took "
			<< (double)(clock() - time) / CLOCKS_PER_SEC << " seconds." << std::endl;

		time = clock();
		Set<int> s = primes(count_elems);
		std::cout << "Generating set of primes in range [2, " << count_elems << "] took "
			<< (double)(clock() - time) / CLOCKS_PER_SEC << " seconds." << std::endl << std::endl;
	}
}

#endif
