#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include "utils.cpp"

using namespace std;
mutex mtx; 

/* if we intended to sum each varible using mutex this mean that we have a 0 speed and we running sequntialy and this is a bad implementation 
so we can just compute a local sum of the all values the thread have then add this value on the global sum varible and this will solve the problem 
well , taking advantage of multi threading  */

void sum(int start, int end , vector<double>& vec , double& globalSum) {
    double localSum = 0; /* computing local sum */
    for (int i = start; i < end; ++i) {
        localSum += vec[i];
    }
    
    /* locking then compute the global sum */
    lock_guard<mutex> lock(mtx);
    globalSum += localSum;
}


int main() {

    int NUM_THREADS = 8; 
    double globalSum = 0;

    vector<double> vec = generateRandomVector(100 , 0 , 100); // generating a random vector of size 100 varying from 0 to 100 


    int chunkSize = vec.size() / NUM_THREADS;  

    vector<thread> threads;


    /* using  the same previous procedure to create a vector of threads and emplacing back each function into thread putting start and end using 
    to equally distribute each chunk of data into a thread */
    for (int i = 0; i < NUM_THREADS; ++i) {
        int start = i * chunkSize;
        int end = (i == NUM_THREADS - 1) ? vec.size() : (i + 1) * chunkSize;
        threads.emplace_back(sum, start, end , ref(vec), ref(globalSum));
    }

    for (auto& t : threads) {
        t.join();
    }

    cout << "Global sum: " << globalSum << endl;

    return 0;
}
