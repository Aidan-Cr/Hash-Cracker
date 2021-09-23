//include librarys
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
#include <sstream>

//include files
#include "task.h"
#include "Hash.h"
#include "Farm.h"
#include "Parse.h"

using std::chrono::duration_cast;
using std::chrono::microseconds;
typedef std::chrono::steady_clock the_clock;
using namespace std;

int main() {
    //initalise local variables
    Farm f;
    string line;
    atomic<bool> found = false;
    atomic<bool> parsed = false;
    mutex mux;
    string input;
    ifstream myfile;

    //send message to display
    cout << "please enter a password" << '\n';

    //get input form keyboard
    cin >> input;
    string pass = input;

    //loop implimented for testing purposes
    for (int l = 0; l < 100; l++) {

        //open dictionary file
        myfile.open("rockyou.txt");

        //format input in a way that the MD5 hash algorithm can interprit
        string parsed_pass;
        parsed_pass.resize(16);
        for (int i = 0; i < 16; i++)
        {
            parsed_pass[i] = static_cast<char>(stoi(pass.substr(i * 2, 2), nullptr, 16));
        }

        //add task to parse dictionary
       if (myfile.is_open())
       {
           f.add_task(new ParseTask(found, parsed_pass, mux, line, f, myfile, parsed));
       }
       else cout << "Unable to open file";

       //start timing code
       the_clock::time_point start = the_clock::now();

       //run then close the farm
       f.run(found, parsed);
       f.join();

       //end timing code
       the_clock::time_point end = the_clock::now();
       
       //close dictionary
       myfile.close();

       //format and output timings
       double time_taken = duration_cast<microseconds>(end - start).count();
       time_taken = (round(time_taken * 100 / 1000000) / 100);
       cout << "Farm took " << time_taken << " s.\n" << l << "\n";

       //output timings to .csv file
       ofstream outputfile;
       outputfile.open("Results.csv", std::ios_base::app);
       outputfile << time_taken << "\n";
       outputfile.close();

       //reset for next loop
       found = false;
       parsed = false;
    }
   return 0;
}