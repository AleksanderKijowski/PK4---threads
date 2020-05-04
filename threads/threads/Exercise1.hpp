#pragma once
#include <iostream>
#include <thread>

void Sum(int values[], int startIndex, int howMany, int & result)
{
	for (auto i = startIndex; i < startIndex + howMany; ++i)
	{
		result += values[i];
	}
}

void Exercise1()
{
	int values[100];

	for (auto i = 0; i < 100; ++i)
	{
		values[i] = i;
	}

	int sum1 = 0;
	int sum2 = 0;

	std::thread t1(&Sum, values, 0, 50, std::ref(sum1));
	std::thread t2(&Sum, values, 50, 50, std::ref(sum2));

	t1.join();
	t2.join();

	auto result = sum1 + sum2;

	std::cout << result << std::endl;
}