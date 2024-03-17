#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

// you can see the documntation of the (this_thread) from here => https://cplusplus.com/reference/thread/this_thread/
// you can see thread library documntation from here => https://www.geeksforgeeks.org/multithreading-in-cpp/


void my_func(int n){
	cout << "Thread ID : " << this_thread::get_id() << "value of n : " << n << endl; 
	this_thread::sleep_for(chrono::seconds(n)); // converting n to seconds using chrono as the the main way to do it is ex: 1000ms (writing into a time domain 
}


int main(){

	cout <<  "main function thread num : " <<this_thread::get_id() << endl;
	thread worker(my_func , 2);
	worker.join();
	return 0;

}
