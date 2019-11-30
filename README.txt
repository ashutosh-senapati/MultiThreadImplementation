

Objective : We have two programs prog1.c and prog2.c. prog1.c is used to show the implementation of single thread execution of the multiplication of large numbers while prog2 is used to show the same functionality using multi-threading. Here we have demonstrated that if we carry out the operation of multiplying two large operands using multi-threading it takes less time as compared to single threading method. 

The multiplication was performed in 1.366236 ms by single threading method while in multi threading method it took 1.122049 ms, which was considerably lower.

Below is the technique we have implemented to achieve the above said objectives.

//create a function multiply to perform multiplication of digits in a accumulator method

//without using intptr_t throws an error cast to pointer from integer of different size

//once number of multiplication upto all thread counts are done and if there is a remaining multiplication intitate it to end and simulate multiplication

// performing number of multiplication which is to be performed per thread

// semaphore set to 0 to maintain mutex

// performing number of multiplication which is to be performed per thread

// signal the semaphore after completion of multiplication in a thread


//in the main() function
// create 2 input files to read the numbers

// initialising mutual exclusion semaphore

// get a size of the first operand and copy the number to an array

// get a size of the first operand and copy the number to an array

// number of multiplications may or may not be equal to number of threads so find the number of multiplications to be done in each thread

// creating threads

// wait until all threads complete their execution

//close all the files

//calculate the cpu time