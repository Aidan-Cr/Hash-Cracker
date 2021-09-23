#ifndef HASHTASK_H
#define HASHTASK_H

//include librarys
#include <string>
#include <mutex>
#include <thread>
#include <atomic>

//include files
#include "task.h"

using namespace std;

class HashTask : public Task
{

public:

	HashTask(atomic<bool>& done, string& Correct_password, mutex& mx, string Line) :
	done(done), Correct_password(Correct_password), mx(mx), line(Line){}

	void run();

private:
	//initialise private variables
	string& Correct_password;
	string line;
	atomic<bool>& done;
	mutex& mx;
};

#endif