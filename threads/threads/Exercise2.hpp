#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <ctime>
#include <mutex>

// Used to protect writing to the vector
std::mutex vectLock;
std::vector<unsigned int> primeVect;

void FindPrimes(unsigned int start,
	unsigned int end) {

	// Cycle through numbers while ignoring evens
	for (unsigned int x = start; x <= end; x += 2) {

		// If a modulus is 0 we know it isn't prime
		for (unsigned int y = 2; y < x; y++) {
			if ((x % y) == 0) {
				break;
			}
			else if ((y + 1) == x) {
				vectLock.lock();
				primeVect.push_back(x);
				vectLock.unlock();
			}
		}
	}
}

int Exercise3()
{
	std::vector<unsigned int> primeVect;

	int startTime = clock();

	FindPrimes(1, 100000);

	// Get time after execution
	int endTime = clock();

	std::cout << "Execution Time : " <<
		(endTime - startTime) / double(CLOCKS_PER_SEC) << std::endl;

	return 0;
}