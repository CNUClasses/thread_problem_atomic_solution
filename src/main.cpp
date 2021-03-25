/*
 * main.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: keith
 */
#include <string>
#include <iostream>
#include <atomic>

#include <thread>

using namespace std;
const int NUMB_TIMES = 100000;

//global variable
//int global2 = 0;

//atomic variable
std::atomic<int> global2(0);

//thread functions
void task_dec() {
	//decrement
	for (int i = 0; i < NUMB_TIMES; i++) {
		global2--;	//this one statement is the critical section
	}
}

void task_inc() {
	//increment
	for (int i = 0; i < NUMB_TIMES; i++) {
		global2++;	//this one statement is the critical section
	}
}

int main() {
	//how many cores do we have? BTW unsigned really? are we planning for 2**32 cores?
	unsigned num_cpus = std::thread::hardware_concurrency();

	// constructs 2 threads and runs
	thread t1(task_inc);
	thread t2(task_dec);
	//in disassembly view the following line
	//equals 3 assembly instructions, interrupt can
	//happen after any of those three
	//global2++;


	// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	t1.join();
	t2.join();

	std::cout << "Value of global      :" << global2 << " it should be 0"
			<< std::endl;

}

