#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <chrono>

constexpr int num_Phil = 5; // Number of philosphers
std::thread philosphers[num_Phil]; // The Philosophers as threads
std::mutex mtx[num_Phil]; //forks as mutexes
std::mutex cout_mutex; // mutex for keeping cout safe
int ate[5] = {0}; // Counting which philosopher ate how many times
int intrupt = 100; // To intrupt dining. I use var - intrupt and decrease it.

void print(std::string str){ // Function for safe printing
    cout_mutex.lock(); // Locking cout, so that none of the other operations will intrupt
    std::cout << str << std::endl;
    cout_mutex.unlock(); // Unlocking after finished printing.
}

void think(int id){ // Philosopher "id" is thinking
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // thinking - time : 500 ms
    print("Philosopher " + std::to_string(id) + " is thinking."); // print
}

bool eat(int id, int left, int right) { // Function, Philosopher "id" is eating (trying to)
    
    while(1) if (mtx[left].try_lock()) { // Philosopher "id" trying to pick up left fork. (keeps going until success)
    	
        print("Philosopher " + std::to_string(id) + " got the fork " + std::to_string(left));
        // He got the fork... So print it.
    	
        if (mtx[right].try_lock()) {
            // Philosopher "id" trying to pick up right fork.
            print("Philosopher " + std::to_string(id) + " got the fork " + std::to_string(right) + 
                "\nPhilosopher " + std::to_string(id) + " eats."); // print
            return true;
        } else {
            mtx[left].unlock(); 
            // Drop the left fork since Philosopher cannot pick up the right one
            // Added so that we can prevent dleadlock & starvation
        }

    }

    return false; // Never going to reach here ...
}

void putDownForks(int left, int right) {
    mtx[left].unlock(); // Put down the left fork
    mtx[right].unlock(); // Put down the right fork
}

void dinner_started(int philID) {
	
    // Left fork and Right forks indexes are determined here
    // There is a method implemented here, Taking the min numbered
    // Fork first...

	// int lIndex = philID;
	// int rIndex = (philID + 1) % (num_Phil);
    int lIndex = std::min(philID, (philID + 1) % (num_Phil));
    int rIndex = std::max(philID, (philID + 1) % (num_Phil));

    //////////////

    while (intrupt-- > 0) { // Intrupt is the var, that I use to give a bound to dinner time
        if (eat(philID, lIndex, rIndex)) { // Philosopher "philID" is trying to eat, w/ forks; lIndex & rIndex
            putDownForks(lIndex, rIndex); // Put down the forks
            ate[philID]++; // This philosopher:"philID" ate one more time...
            std::this_thread::sleep_for(std::chrono::milliseconds(600)); //cannot acquire eating right away
        }
    }

}

void dine(){
	
    // Threads created. Each thread is a philospher. Every philosopher is called function "dinner_started"
    for (int i = 0; i < num_Phil; ++i) philosphers[i] = std::thread(dinner_started, i);
    // Threads joined...
	for (int i = 0; i < num_Phil; ++i) philosphers[i].join();
}

int main() { 
    dine(); // Dinner starts...
    // Just print how many times philosophers ate
    for (int i = 0; i < num_Phil; ++i) std::cout << i << " = " << ate[i] << std::endl;
}