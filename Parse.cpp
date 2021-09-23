//include librarys
#include <iostream>
#include<fstream>
#include <string>
#include<thread>

//include files
#include "Parse.h"
#include "Hash.h"
#include "Farm.h"

using namespace std;

void ParseTask::run(){
    ifstream openfile;
    bool end = false;

    //open dictionary
    openfile.open("rockyou.txt");

    //loop until the end of the dictionary is reached unless the Hash is found
    while (end == false && !done) {
        for (int counter = 0; counter < 100 && !openfile.eof() && !done; counter++) {
            getline(openfile, line);

            //add task to the queue
            f.add_task(new HashTask(done, Correct_password, mx, line));
            if (openfile.eof()) {
                end = true;
            }
        }
    }
    end = false;
    parsed = true;
}