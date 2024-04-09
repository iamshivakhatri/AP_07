#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Part A: NO Synchronization

        int counter1 = 0;
        vector<thread> V;
        int oddcount = 0;
        int evencount = 0;
        int x;

        srand(time(0));

        for (int i = 0; i < 200; ++i) {
            x = rand();

            if (x % 2 == 0)
                evencount++;
            else
                oddcount++;


            V.push_back(thread([&counter1, x]() {
                if (x % 2 == 0)
                    counter1++;
                else
                    counter1--;
            }));
        }

        for (auto& th : V)
            th.join();

        int total = evencount - oddcount;
        cout << "PART A. NO Synchronization" << endl;
        cout << "# of increments is " << evencount << endl;
        cout << "# of decrements is " << oddcount << endl;
        cout << "Correct value should be " << total << endl;
        cout << "Value of counter is " << counter1 << endl << endl;


    // Part B: Synchronized using Mutex

        V.clear();
        counter1 = 0;
        mutex mtx;
        oddcount = 0;
        evencount = 0;




        for (int i = 0; i < 200; ++i) {
            x = rand();

            if (x % 2 == 0)
                evencount++;
            else
                oddcount++;

            V.push_back(thread([&counter1, &mtx, x]() {
                mtx.lock();
                if (x % 2 == 0)
                    counter1++;
                else
                    counter1--;
                mtx.unlock();
            }));

        }

        for (auto& th : V)
            th.join();

        total = evencount - oddcount;
        cout << "PART B. Mutex" << endl;
        cout << "# of increments is " << evencount << endl;
        cout << "# of decrements is " << oddcount << endl;
        cout << "Correct value should be " << total << endl;
        cout << "Value of counter is " << counter1 << endl << endl;


    // Part C: Synchronization with atomic<int>

        V.clear();
        atomic<int> counter2(0);
        oddcount = 0;
        evencount = 0;



        for (int i = 0; i < 200; ++i) {
            x = rand();

            if (x % 2 == 0)
                evencount++;
            else
                oddcount++;



            V.push_back(thread([&counter2, x]() {
                if (x % 2 == 0)
                    counter2++;
                else
                    counter2--;
            }));
        }

        for (auto& th : V)
            th.join();

        total = evencount - oddcount;
        cout << "PART C. atomic<int>" << endl;
        cout << "# of increments is " << evencount << endl;
        cout << "# of decrements is " << oddcount << endl;
        cout << "Correct value should be " << total << endl;
        cout << "Value of counter is " << counter2 << endl << endl;


    return 0;
}

/***
/Users/shivakhatri/Documents/College/Advanced_Programming/khatri_shiva_prog7/cmake-build-debug/khatri_shiva_prog7
PART A. NO Synchronization
# of increments is 103
# of decrements is 97
Correct value should be 6
Value of counter is 5

PART B. Mutex
# of increments is 103
# of decrements is 97
Correct value should be 6
Value of counter is 6

PART C. atomic<int>
# of increments is 100
# of decrements is 100
Correct value should be 0
Value of counter is 0
 */


/**
 /Users/shivakhatri/Documents/College/Advanced_Programming/khatri_shiva_prog7/cmake-build-debug/khatri_shiva_prog7
PART A. NO Synchronization
# of increments is 105
# of decrements is 95
Correct value should be 10
Value of counter is 12

PART B. Mutex
# of increments is 110
# of decrements is 90
Correct value should be 20
Value of counter is 20

PART C. atomic<int>
# of increments is 101
# of decrements is 99
Correct value should be 2
Value of counter is 2

 */
