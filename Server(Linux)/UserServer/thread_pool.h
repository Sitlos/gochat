#pragma once

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <atomic>
#include <functional>

#include"util.h"

namespace gochat {

	template <typename T>
	class SyncQueue
	{
	public:
		SyncQueue(int maxSize) : max_size_(maxSize), need_stop(false) { }
		//添加事件
		void Put(const T& x);
		//添加事件
		void Put(T && x);
		//从队列中取事件,取所有事件
		void Take(std::list<T> &list);
		//取一个事件
		void Take(T &t);
		//终止同步队列
		void Stop();
		//队列为空
		bool Empty();
		//队列为满
		bool Full();
		//队列大小
		size_t Size();
		//队列大小
		int Count();
	private:
		//队列不为满
		bool NotFull() const;
		//队列不为空
		bool NotEmpty() const;

		void Add(T && x);
		//缓冲区
		std::list<T> queue_;
		//互斥量
		std::mutex mutex_;
		//队列不为空的条件变量
		std::condition_variable not_empty_;
		//队列不为满的条件变量
		std::condition_variable not_full_;
		//任务队列最大长度
		int max_size_;
		//终止的标识,当为true时代表同步队列要终止
		bool need_stop;

	};


	class ThreadPool
	{
	public:
		using Task = std::function<void()>;

		ThreadPool(int numThreads = std::thread::hardware_concurrency()) :queue_(kMaxTaskCount) {
			Start(numThreads);
		}

		~ThreadPool();

		//保证多线程环境下只调用一次StopThreadGroup函数
		void Stop();

		//添加任务,右值完美转发
		void AddTask(Task && task);

	private:
		//建立numThreads个数的线程组
		void Start(int numThreads);
		//取出任务队列中的全部,依次执行
		void RunInThread();
		//终止所有任务的执行
		void StopThreadGroup();
		//处理任务的线程组
		std::list<std::shared_ptr<std::thread>> thread_group;
		//同步队列
		SyncQueue<Task> queue_;
		//运行的标志,flase代表终止
		std::atomic_bool running_;
		//保证在函数在多线程环境中只被调用一次
		std::once_flag flag_;
	};

}

