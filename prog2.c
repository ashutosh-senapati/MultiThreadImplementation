/*
Ashutosh Senapati
axs190030
2021480970

Monish Alur Gowdru
mxa190025
2021496780

Class : OS 5348.001
Project : OS Project 02

*/



#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define input_size 1000000
#define output_size 2000000

int number1[input_size];
int number2[input_size];
int result[output_size];

int numsize1, numsize2, mult_in_one_thread, thread_count,leftover_mul;

sem_t semaphore;

pthread_t tid[ 50 ]; 

void *multiply(void *args)
{
//without using intptr_t throws an error cast to pointer from integer of different size

	int thread_number = (intptr_t)args;
	
	int i, j;
//start and end are 	
	int start, end;
	int res;
	start = thread_number * mult_in_one_thread;
	end = start + mult_in_one_thread - 1;
	
//once number of multiplication upto all thread counts are done and if there is a remaining multiplication intitate it to end and simulate multiplication
	
	if(thread_number == thread_count - 1)
		end =  end + leftover_mul;
    	
// semaphore set to 0 to maintain mutex
	sem_wait( &semaphore );
	

// performing number of multiplication which is to be performed per thread

	for(i = 0;i< numsize2;++i){
		for(j = start; j<=end; ++j){
			res = number1[j] * number2[i];
			
			result[i + j] += res % 10;
			result[i + j +1] += res / 10;
			
		}
	}
// signal the semaphore after completion of multiplication in a thread

	sem_post( &semaphore );
}

int main()
{
// create 2 input files to read the numbers

	FILE* fp1;

	fp1 = fopen("a.txt","r");
	
	FILE* fp2;
	
	fp2 = fopen("b.txt","r");
	

	numsize1=0; 
	numsize2=0;
	
	char ch;

// initializing mutual exclusion semaphore

	sem_init( &semaphore, 0, 1 );
	
	printf("Enter thread count \n");
	
	scanf("%d",&thread_count);
    	
   
	int flag=0;
	
	int l=0;
	
	int i;
	
// get a size of the first multiplicant and copy the number to an array

	while((ch = fgetc(fp1)) != '|'){
	
	l=(l * 10) + ch - '0';
	
	}
	
	i = 0;


	numsize1 = l;
	
	while((ch = fgetc(fp1)) != EOF){
	
	number1[numsize1 - (i + 1)]=ch-'0';
	i++;
	
	}
	
// get size of second multiplicant and copy the number to an array

	l = 0;

	while((ch = fgetc(fp2)) != '|'){

	l=(l * 10) + ch - '0';

	}	


	i = 0;

	numsize2 = l;

	while((ch = fgetc(fp2)) != EOF){
		
		number2[numsize2 - (i + 1)] = ch-'0';
		i++;
	}

// number of multiplications may or maynot be equal to number of threads so find the number of multiplications to be done in each thread

	mult_in_one_thread = numsize1/thread_count;
    	
	leftover_mul = numsize1 % thread_count;

// creating threads
	
	for( i = 0; i < thread_count; i++) 
	{
		pthread_create( &tid[ i ], NULL, multiply, (void *)(intptr_t)i );
	}

// wait until all threads complete their execution


	for( i = 0; i < thread_count; i++ ) 
		pthread_join( tid[ i ], NULL );


	
	for(i = 0; i < output_size;++i){
		result[i + 1] = result[i+1] + (result[i]/10);
		result[i] %= 10;
	}

	
	int nresult =  numsize1+numsize2 - 1;
    
	while(result[nresult] == 0){

	nresult--;

	}

 	FILE* fp3;
	
	fp3 = fopen("c2.txt","w");
   	
	for(i = nresult; i >= 0; --i){

	fprintf(fp3,"%d", result[i]);
	printf("\n");

	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

}
