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

namespace ThreadPool
{
	class ThreadPool
	{

	private:

		size_t pool_size;
		std::vector<std::thread> worker_threads;
		std::queue <std::function<void()>> jobs;

		std::condition_variable cv_job_q;
		std::mutex m_job_q;

		bool stop_all;


	public:

		ThreadPool(size_t _pool_size) : pool_size(_pool_size), stop_all(false) {

			worker_threads.reserve(pool_size);

			for (size_t i = 0; i < pool_size; i++)
			{
				worker_threads.emplace_back([this]() {this->WorkerThread(); });
			}

		}
		ThreadPool(const ThreadPool& other) = delete;

		~ThreadPool();



	public:

		void WorkerThread();
		
		template<typename F, typename... Args>
		std::future<typename std::invoke_result<F, Args...>::type> EnqueuJob(F&& func, Args&&... args );


	};

	void ThreadPool::WorkerThread()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(m_job_q);

			cv_job_q.wait(lock, [this]() {return !this->jobs.empty() || stop_all; });

			if (stop_all && this->jobs.empty()) return;

			std::function<void()> job = std::move(jobs.front());
			jobs.pop();
			lock.unlock();

			job();
		}
	}

	template<typename F, class... Args>
	std::future<typename std::invoke_result<F, Args...>::type> ThreadPool::EnqueuJob(F&& func, Args&&... args)
	{
		if (stop_all)
		{
			throw std::runtime_error("Thread Pool »ç¿ë ÁßÁö µÊ");
		}

		using return_type = typename std::invoke_result<F,Args...>::type;
		
		auto job = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(func),std::forward<Args>(args)...));

		std::future<return_type> job_result_furture = job->get_future();
		{
			std::lock_guard<std::mutex> lock(m_job_q);
			jobs.push([job]() {(*job)(); });
		}

		cv_job_q.notify_one();

		return job_result_furture;

	}

	ThreadPool::~ThreadPool()
	{
		stop_all = true;
		cv_job_q.notify_all();

		for (auto& t : worker_threads)
		{
			t.join();
		}
	}
}

int work(int t, int id)
{
	printf("%d start\n", id);
	std::this_thread::sleep_for(std::chrono::seconds(t));

	printf("%d end after %ds\n", id, t);
	
	return id + t;
}

//int main()
//{
//	
//	ThreadPool::ThreadPool pool(3);
//
//	std::vector<std::future<int>> futures;
//
//	for (int i = 0; i < 10; i++)
//	{
//		futures.emplace_back(pool.EnqueuJob(work, i % 3 + 1, i));
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		printf("result : %d \n", futures[i].get());
//	}
// 
//}  