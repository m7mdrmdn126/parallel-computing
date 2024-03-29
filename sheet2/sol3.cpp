#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int BUFFER_SIZE = 5;


/* creating a buffer to be shared between teh producer and consumer */
vector<int> buffer;
mutex mtx; // here i am creating a mutex object to and unlock 


void producer() {
    for (int i = 0; i < 10; ++i) {
       
       // in this line im locking and entering the critical section
        unique_lock<mutex> lock(mtx);


        if (buffer.size() == BUFFER_SIZE) {
            /* checking if buffer is full so unlock and wait till the consumer consume */
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(100)); 

        } else {

            /* if the buffer is not full so we produce new elemnt into our buffer */
            int item = i;
            buffer.push_back(item);
            cout << "Produced: " << item << endl;

            /* and then releasing the lock */
            lock.unlock();
        }
    }
}



void consumer() {
    for (int i = 0; i < 10; ++i) {
    

        unique_lock<mutex> lock(mtx);
        /* here we lock and enter into the critical section */

 
        if (buffer.empty()) {

            /* if we have empty buffer we cannot consume so we get out the critical section and unlock 
            then  we sleep to simulate waiting the producer ro produce */
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(100));
        } 
        
        else {

            /* if there is items we 're going to consume then unlock */
            
            int item = buffer.back();
            buffer.pop_back();
            cout << "Consumed: " << item << endl;

            lock.unlock();
        }
    }
}

int main() {
   
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
