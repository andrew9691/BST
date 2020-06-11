#include <iostream>
#include "BST.h"
#include "TestBST.h"

using namespace std;
using namespace testBST;

int main()
{
	BST<int> t1(20);
	t1.add(14);
	t1.add(50);
	t1.add(42);
	t1.add(9);
	t1.add(18);
	t1.add(23);
	t1.add(2);
	t1.add(10);

	// t1.ordered_print();
	// t1.del_elem(20);
	// t1.ordered_print();

	//t1.stack_print();
	t1.print_lays();

	// BST<int> t2(20);
	// t2.add(5);
	// t2.add(4);
	// t2.add(9);
	// t2.add(8);
	// t2.add(0);
	// t2.add(2);
	// cout << trees_are_equal(t1, t2) << endl;

	// Set<int> primes_set = primes(100);
	// primes_set.print();
	// cout << endl;
	//
	// std::vector<int> primes_vec = primesVector(100);
	// for (int x : primes_vec)
	// 	cout << x << " ";
	// cout << endl << endl;

	/// Compare two implementations of sieve of Eratosthenes
	// testPrimes(5000);
	// testPrimes(10000);
	// testPrimes(20000);
	// testPrimes(50000);
}
