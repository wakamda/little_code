#include "ThreadPool.hpp"
#include <iostream>

void loop(int num) {
    // 这里是你想要执行的循环函数
    // 可以是任何函数体，接受参数并且返回void
    std::cout << "Loop " << num << std::endl;
}

int main(int argc,char* argv[])
{
    ThreadPool pool(5);

    for (int i = 0; i < 5; ++i) {
        pool.enqueue(loop,i);
    }

    // 等待一段时间以确保任务执行完毕
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}