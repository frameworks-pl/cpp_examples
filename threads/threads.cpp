#include <..\include\gtest\gtest.h>
#include <thread>
#include <mutex>


void threadFunction(int* pResult) {

    *pResult = 10;

}


class MyThread {

    public:
        void operator()(int value, int* pResult) {
            *pResult += value;
        }

};


TEST(Threads, SimpleFunctionThread) {

   int result = 0;
   std::thread thread(threadFunction, &result);
   thread.join();

   ASSERT_EQ(10, result);

}

TEST(Threads, ThreadPoolWithJoin) {

    int result = 0;
    int* pResult = &result;
    std::vector<std::thread> threads;
    static std::mutex m;


    for (int i = 0; i < 10; i++)  {
        threads.emplace_back(            
            [pResult, i]() {

                m.lock();
                *pResult += i;
                m.unlock();
            }
        );
        
    }

    for (auto& thread : threads) {
        thread.join();
    }

    ASSERT_EQ(45, result);

}