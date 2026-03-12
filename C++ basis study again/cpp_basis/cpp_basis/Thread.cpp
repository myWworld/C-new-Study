#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include<chrono>
#include <queue>
#include <string>
#include <condition_variable>
#include <atomic>
#include <future>


class ThreadPool
{
	size_t pool_size;
	std::vector<std::thread> thread_pool;
	

public:

	ThreadPool(size_t _pool_size): pool_size(_pool_size) {}
	ThreadPool(const ThreadPool& other) = delete;


public:

	template<typename F, typename... Args>
	void AddWork(F&& func, Args&&... args)
	{

	}
};

int main()
{
	

 
}  