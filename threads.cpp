#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

#define i {1,3,5,7,9}
#define j {2,4,6,8,10}

enum class ready_states {
    default_state, 
    first_ready,
    second_ready
}; 

std::mutex mtx;
std::condition_variable cv;
ready_states ready = ready_states::default_state;

void DoSomeShiet(){
    for(const auto n : i){
        std::cout << "DoSomeShiet. ID: " << std::this_thread::get_id() << " - " << n << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

// void print(const auto& n){
//     std::cout << n << " ";
// }

void first(){
    for(int n:i)
    {
        {
            std::unique_lock lock(mtx);
            cv.wait(lock, []() {return ready == ready_states::first_ready || ready == ready_states::default_state;});
            std::cout << n << " ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ready = ready_states::second_ready;
        }
        cv.notify_all();
    }
}

void second(){
    for(int n:j)
    {
        {
            std::unique_lock lock(mtx);
            cv.wait(lock, []() {return ready == ready_states::second_ready;});
            std::cout << n << " ";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ready = ready_states::first_ready;
        }
        cv.notify_all();
    }
}

int main()
{
    std::thread th1(first);
    std::thread th2(second);

    th1.join();
    th2.join();

    std::cout << "\tfinished" << std::endl;
    
    return 0;
}