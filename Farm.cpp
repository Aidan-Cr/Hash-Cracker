//include librarys
#include<thread>
#include<iostream>
#include<fstream>
#include<string>
#include<thread>
#include<atomic>
#include<chrono>

//include files
#include "Farm.h"
#include "Hash.h"

using namespace std;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
typedef std::chrono::steady_clock inner_clock;

void Farm::add_task(Task* task) 
{
    //lock mutext to protect data
    task_mutex.lock();
    //add a task to the queue
	to_do.push(task);
    //unlock the mutext
    task_mutex.unlock();
}

void Farm::run(atomic<bool>& found, atomic<bool>& parsed)
{
    //determine number of cores on machine
    int num_cores = 0;
    num_cores = std::thread::hardware_concurrency();

        for (auto i = 0; i < num_cores; i++) {
            //add a tread for every core in the machine
            thread_vector.push_back(new thread([&] {
                //loop unil hash matched
                while (found == false) {

                    //lock mutext to protect data
                    task_mutex.lock();

                    //if queue still has tasks then run a task
                    if (!to_do.empty()) {

                        Task* current_task = to_do.front();
                        to_do.pop();
                        task_mutex.unlock();

                        current_task->run();
                        delete current_task;
                    }
                    //if hash cannot be found then exit loop
                    else if (to_do.empty() && parsed == true) {
                        task_mutex.unlock();
                        break;
                    }
                    else{
                        task_mutex.unlock();
                    }
                }
            }));
        }
        
    cout << "All done\n";
}

void Farm::join()
{
    //join threads together
    for (auto i = 0; i < thread_vector.size(); i++) {
        thread_vector[i]->join();
        delete thread_vector[i];
    }
    thread_vector.clear();
    //delete leftover tasks
    while (!to_do.empty()) {
        Task* x = to_do.front();
        delete x;
        to_do.pop();
    }
}