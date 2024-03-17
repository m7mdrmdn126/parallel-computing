/* NOTE : i think that the question is not so clear as there is no diffrence between this problem and q3 except we will multiply 
each number by (i+1) but i think the right formulation is we need to multiply all the elements in the array each one by the next number 
as if ex: assume an array => [3 , 4 , 5 , 6] , then we need to multiply 3*4 = 12 and then we multiply 12 * 5 etc .. 
so we will solve it on this manner as this is the challanging way of that task . */


#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<random>

using namespace std;

void mult(vector<int> arr, int start , int end, long long* result){ // in this function we take a start and end of a vector to make our algo on .
    for (int i = start; i<end; ++i){
        *result *= arr[i];
    }
}


vector<int> generate_random_vector(int size , int min , int max){
    /* don't mind your self with this function it is just generating a random vector so we can check our algorithm on */

    random_device rd; 
    std::mt19937 gen(rd()); // generator 

    uniform_int_distribution<int> distribution(min, max);
    vector<int> randomVector;
    for (int i = 0; i < size; ++i) {
        randomVector.push_back(distribution(gen));
    }

    return randomVector;
}

void print_vector(vector<int> vec){
    for(auto &i : vec)
        cout << i << " ";
}


int main(){

    int SIZE = 100; // we will work with a vector 20 sized in this example testing the diffrence in time
    vector<int> vec = generate_random_vector(SIZE , 1 , 10);


    /* you need to that the multiplication of 100 numbers in each other will result a very huge number expremintly the long long type is not holding this 
    you can use the utilits i'm providing to check after some iterations the result will be 0 */
   

    // sequntial 

    auto start = std::chrono::high_resolution_clock::now();
    long long result = 1; // a varible put our sequntial result in ; it has to be intiated to one as we will multiply on it.
    mult(vec , 0 , SIZE , &result);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = (end - start).count();
    cout << "the sequntial approach took : " <<  duration << "ms." << endl;




    //multi threading 

    auto start_para = std::chrono::high_resolution_clock::now();

    int number_of_threads = 10;
    int chunck = SIZE / number_of_threads ;
    int final_result = 1;

    vector<thread> threads(number_of_threads);
    long long results[number_of_threads] = {0} ;

    for(int i = 0; i< number_of_threads; ++i)
        threads[i] = thread(mult , vec ,  i , i+chunck , results+i) ; // in this line i'm using the name of the array as a refrence(address) if u can't get it watch this quickly ==> https://www.youtube.com/watch?v=gv-y9hIhvq4 

    for(auto &thrd : threads) // joining threads 
        thrd.join();

    for(int i = 0; i<number_of_threads; ++i) 
        final_result *= results[i];

    auto end_para = std::chrono::high_resolution_clock::now();

    auto duration_para = (end_para - start_para).count();
    cout << "the parallel approach took : " <<  duration_para << "ms." << endl;
}