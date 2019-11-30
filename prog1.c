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

pthread_t tid;

void *multiply(void *args)
{
//without using intptr_t throws an error cast to pointer from integer of different size

	
	
	int i, j;	
	int res;
// performing number of multiplication which is to be performed per thread

	for(i = 0;i< numsize2;++i){
		for(j = 0; j<=numsize1; ++j){
			res = number1[j] * number2[i];
			
			result[i + j] += res % 10;
			result[i + j +1] += res / 10;
			
		}
	}


	
}

int main()
{
// create 2 input files to read the numbers

	clock_t t;
	t=clock();

	FILE* fp1;

	fp1 = fopen("a.txt","r");
	
	FILE* fp2;
	
	fp2 = fopen("b.txt","r");
	

	numsize1=0; 
	numsize2=0;
	
	char ch;
	
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

// creating thread
	
	pthread_create( &tid, NULL, multiply, NULL );
	

// wait until thread complete it's execution
		pthread_join( tid, NULL );


	
	for(i = 0; i < output_size;++i){
		result[i + 1] = result[i+1] + (result[i]/10);
		result[i] %= 10;
	}

	
	int nresult =  numsize1+numsize2 - 1;
    
	while(result[nresult] == 0){

	nresult--;

	}

 	FILE* fp3;
	
	fp3 = fopen("c1.txt","w");
   	
	for(i = nresult; i >= 0; --i){

	fprintf(fp3,"%d", result[i]);
	//printf("\n");

	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	t = clock() - t;

	double total_t = ((double)t) / CLOCKS_PER_SEC;
	
	printf("Total time taken by CPU single thread: %f\n", total_t);



}
