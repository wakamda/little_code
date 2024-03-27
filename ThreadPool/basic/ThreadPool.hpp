#ifndef THREADPOLL_H_
#define THREADPOLL_H_

#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <future>
#include <mutex>
#include <condition_variable>


class ThreadPool{
public:
    ThreadPool(int size);

    ~ThreadPool();

    template<typename F, typename... Args>
    void enqueue(F&& f, Args&&... args);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool isstop;
};

ThreadPool::ThreadPool(int size):isstop(false)
{
    for(int i = 0; i< size; ++i)
    {
        workers.emplace_back(
            [this]
            {
                while(true)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->condition.wait(lock,[this]{
                            return this->isstop || !this->tasks.empty();
                        });
                        if(this->isstop && this->tasks.empty()){
                            return;
                        }
                        task = std::move(tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
                
            }
        );
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        isstop = true;
    }

    condition.notify_all();
    for(std::thread &worker : workers){
        worker.join();
    }
}

//插入任务
template<typename T,typename... Args>
void ThreadPool::enqueue(T&& t,Args&&... args)
{
    using ReturnType = typename std::result_of<T(Args ...)>::type;

    auto func = std::bind(std::forward<T>(t),std::forward<Args>(args)...);

    auto task = std::make_shared<std::packaged_task<ReturnType()>>(func);

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if(isstop){

        }
        this->tasks.push([task](){ (*task)();});
    }
    condition.notify_one();
}

#endif //THREADPOLL_H_