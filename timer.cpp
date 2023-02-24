#include <chrono>
#include <thread>
#include <iostream>

using namespace std::literals::chrono_literals;

struct Timer{
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<float> duration;

        Timer(){
                start = std::chrono::high_resolution_clock::now();      
        }

        ~Timer(){
                end = std::chrono::high_resolution_clock::now();
                duration = end - start;

                float ns = std::chrono::duration_cast<std::chrono::nanoseconds>;
                std::cout << "Timer took " << duration << "nano seconds\n";
                
        }
};

void Function(){
        for (int i = 0; i < 100; i++)
        std::cout << "Hello\n";
}

void main (){
        Function;

        std::cin.get();
}