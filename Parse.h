#ifndef PARSE_H
#define PARSE_H

//include librarys
#include <string>
#include <mutex>
#include <thread>
#include <atomic>

//include files
#include "task.h"
#include "Farm.h"

using namespace std;

class ParseTask : public Task 
{

public:

	ParseTask(atomic<bool>& done, string& Correct_password, mutex& mx, string& line, Farm& f, ifstream& myfile, atomic<bool>& parsed) :
		done(done), Correct_password(Correct_password), mx(mx), line(line), f(f), myfile(myfile), parsed(parsed){}

	void run();

private:
	//initialise private variables
	string& Correct_password, &line;
	atomic<bool>& done;
	atomic<bool>& parsed;
	mutex& mx;
	Farm& f;
	ifstream& myfile;
};

#endif