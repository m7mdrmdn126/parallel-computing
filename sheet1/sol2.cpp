#include<iostream>
#include<thread>
#include<math.h>
#include<vector>

using namespace std;


//  ** utility **
int hint_add(int n){
    return pow(((n+1)/2) , 2); // using this mathmatical formula will solve the problem in o(1) which will make it silly to use threading , this just for illustration as a hint function
    // you can spot the proof there => https://www.quora.com/What-is-the-sum-of-odd-numbers-from-1-to-n
}



/*  ----------------------------------------------------------------------------------------------------------------------  */


void add_func(int* ptr , int n){ // this is a function takes a pointer and an integer then adds the sum of odds in a for loop
    for(int i = 1; i<=n ; i +=2)
        *ptr += i;
} // feeling that you don't understand pointers ? watch this ==> https://www.youtube.com/watch?v=rtgwvkaYt1A



int main(){
  
  
    int number_of_threads = 10;
    int num = 10000;
    int num_per_thread = num / number_of_threads ;
    int final_result = 0;

    // creating a vector that holds all the threads to making sure i can access them and an array with the same number of threads to give each place in this array into a thread as a pointer to 
    // put the sum into it ; afterwards looping on every thread to join it 
    vector<thread> threads(number_of_threads);
    int results[number_of_threads] = {0} ;

    for(int i = 0; i< number_of_threads; ++i)
        threads[i] = thread(add_func , (results+i) , num_per_thread) ; // in this line i'm using the name of the array as a refrence(address) if u can't get it watch this quickly ==> https://www.youtube.com/watch?v=gv-y9hIhvq4 

    for(auto &thrd : threads) // joining threads 
        thrd.join();

    for(int i = 0; i<number_of_threads; ++i) // adding all the results
        final_result += results[i];

    cout << final_result ;
    
    
    return 0;
}