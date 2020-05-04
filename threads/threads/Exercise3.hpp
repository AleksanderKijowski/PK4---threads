#pragma once
#include <thread>
#include <iostream>
#include <mutex>
#include <deque>

const int MaxBufforSize = 50;
std::mutex mtx;
std::condition_variable condition;
std::deque<int> buffor;

void Produce(int howMany)
{
	while (howMany > 0)
	{
		std::unique_lock<std::mutex> locker(mtx);
		condition.wait(locker, []() { return buffor.size() < MaxBufforSize; });
		buffor.push_back(howMany);
		--howMany;
		std::cout << "Produced value:" << howMany << std::endl;
		locker.unlock();
		condition.notify_one();
	}
}

void Consume()
{
	while (true)
	{
		std::unique_lock<std::mutex> locker(mtx);
		condition.wait(locker, []() { return !buffor.empty(); });
		auto value = buffor.back();
		buffor.pop_back();
		std::cout << "Consumed value:" << value << std::endl;
		locker.unlock();
		condition.notify_one();
	}
}

void Exercise4()
{
	std::thread produce(Produce, 100);
	std::thread consume(Consume);

	produce.join();
	consume.join();
}