#include<iostream>
#include<mutex>
#include<thread>

using namespace std;

mutex ostreamLock;

void print_unsafe(){
    cout << "hello from thread : "<< this_thread::get_id() << endl ;
}

void print_safe(){ // uisng mutex to lock and unlock the output stream
    ostreamLock.lock();
    cout << "hello from thread : "<< this_thread::get_id() << endl ;
    ostreamLock.unlock();
}


void execute(int number_of_threads , void (*fnc)()){ // a function to execute any function in a n of threads i passed her a function as a prameter u don't need to do this 
    // but you can see how to do it from here => https://www.geeksforgeeks.org/passing-a-function-as-a-parameter-in-cpp/
    thread threads[number_of_threads];

    for(int i = 0; i<number_of_threads; ++i)
        threads[i] = thread(fnc);

    for(int i = 0; i<number_of_threads; ++i)
        threads[i].join();
}


int main() {

    int number_of_threads = 100 ;

    cout << "printing unsafe .............. " << endl;
    execute(number_of_threads , print_unsafe) ;
    cout << "****************************************************************************************************" << endl;
    cout<< "printing safe ................" << endl ;
    execute(number_of_threads , print_safe);


    return 0;
}