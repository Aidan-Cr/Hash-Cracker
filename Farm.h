#ifndef FARM_H
#define FARM_H

//include librarys
#include <queue>
#include <mutex>
#include <atomic>

//include files
#include "task.h"

using namespace std;

class Farm {
public:

	void add_task(Task* task);

	void run(atomic<bool>& found, atomic<bool>& parsed);

	void join();

private:
	//initialise private variables
	queue<Task*>to_do;
	Task* T;
	mutex task_mutex;
	vector<thread*>  thread_vector;
};
#endif