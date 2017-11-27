/*
 * main.cpp
 *
 *  Created on: Oct 9, 2017
 *      Author: keith
 */
#include <string>
#include <iostream>
#include <thread>
#include <atomic>

using namespace std;
const int FIVE_MILLION = 5000000;

//global variable
int global2 = 0;

//atomic variable
std::atomic<int> atomicglobal(0);

//thread functions
void task_dec() {
	//decrement
	for (int i = 0; i < FIVE_MILLION; i++) {
		global2--;	//this one statement is the critical section
		atomicglobal--;
	}
}

void task_inc() {
	//increment
	for (int i = 0; i < FIVE_MILLION; i++) {
		global2++;	//this one statement is the critical section
		atomicglobal++;
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
	//imaglobal++;

	// Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
	t1.join();
	t2.join();

	std::cout << "Value of global      :" << global2 << " it should be 0"
			<< std::endl;
	std::cout << "Value of atomicglobal:" << atomicglobal << " it should be 0"
			<< std::endl;
}

