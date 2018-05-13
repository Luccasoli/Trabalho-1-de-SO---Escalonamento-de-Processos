/*
#include<iostream>
#include<chrono>
typedef std::chrono::high_resolution_clock Clock;

int main()
{
    auto t1 = Clock::now();
    for(int i = 0; i < 100000; i++){

    }
    auto t2 = Clock::now();
    std::cout << "Delta t2-t1: " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;
}*/

#include <iostream>
#include <cstdio>
#include <ctime>

int main() {
    std::clock_t start;
    double duration;

    start = std::clock();

    /* Your algorithm here */
for(int i = 0; i < 100000; i++){

    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration << " segs\n";
}