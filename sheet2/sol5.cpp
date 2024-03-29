
#include<thread>
#include<iostream>
#include<mutex>

using namespace std;

/* in this code im just using the code provided in the slides to test so you can be able to test and see how it works */



/* if you are struggling to read this class i recomend reading this => https://www.w3schools.com/cpp/cpp_classes.asp*/
class TicketCounter {
    private:
    /* defining the needed varibles as private varibles */
        int availableTickets;
        mutex mtx;

    public:
        TicketCounter(int totalTickets) : // defining constructor
        availableTickets(totalTickets) {}

    void sellTickets(int numTickets) {
        lock_guard<mutex> lock(mtx); // RAII for mutex locking
        /* the RAII lock_guard is a function where you lock and it unlocks automatically , so here we are locking and then checking the condtion if the avilable tickets is enough
        then sleeping to simulate like processing then making the selling process it will unlock when the process finished 
        automatically . */
            if (availableTickets >= numTickets) {
            // Simulate selling tickets
            this_thread::sleep_for(chrono::milliseconds(100));
            // Sell tickets
            availableTickets -= numTickets;
            cout << "Sold " << numTickets << " tickets. Remaining tickets: " << availableTickets << endl;
        }
        else {
        cout << "Not enough tickets available." << endl;}
    }
};

int main() {
    TicketCounter ticketCounter(100); // Total number of tickets available
    // Three people want to buy tickets
    thread t1(&TicketCounter::sellTickets,&ticketCounter, 3);
    thread t2(&TicketCounter::sellTickets,&ticketCounter, 5);
    thread t3(&TicketCounter::sellTickets,&ticketCounter, 2);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}