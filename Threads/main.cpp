#include <iostream>
#include <thread>
#include <Windows.h>
using namespace std;

bool finish = false;

void Hello()
{
	while (!finish)
	{
		cout << "+";
		Sleep(100);
	}
}
void World()
{
	while (!finish)
	{
		cout << "-";
		Sleep(100);
	}
}


void main()
{
	std::thread hello_thread(Hello);
	std::thread world_thread(World);

	cin.get();
	finish = true;

	world_thread.join();
	hello_thread.join();
}
