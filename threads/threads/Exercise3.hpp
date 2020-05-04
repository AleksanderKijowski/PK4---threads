#pragma once
#include <thread>
#include <iostream>
#include <mutex>


void Produce(int howMany)
{
}

void Consume()
{
}

void Exercise4()
{
	std::thread produce(Produce, 100);
	std::thread consume(Consume);

	produce.join();
	consume.join();
}