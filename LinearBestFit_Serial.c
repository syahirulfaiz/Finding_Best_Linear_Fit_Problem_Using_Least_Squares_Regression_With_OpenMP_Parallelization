#include <stdio.h>
#include <math.h>
#include <sys/time.h>  // for timing functions

#define N 50000000	//set the number of points in quadrant
#define eps 1.0E-06	//set the computation tolerance, eps

//global vars of points
double x[N];
double y[N];

double f(double x);	//function declaration of 'f' for calculating y
int main(){
		struct timeval t1, t2, t3, t4;	// for timing
		gettimeofday(&t1, NULL); //begin timing of WHOLE CODE
		
		//----WHOLE CODE----
		double sum_xy=0, sum_x=0, sum_y=0, sum_x_square=0, square_sum_x=0, m=0, c=0;
		int i;	//for iteration

		gettimeofday(&t2, NULL); //start of timing of LOOP REGION
		//----LOOP REGION---
		for(i=0;i<N;i++){
			//define x and y vectors
			x[i]=i/1003.01;	 
			y[i]=f(x[i]);	
			
			//calc sum xy
			sum_xy += x[i]*y[i]; 
			//calc sum x
			sum_x += x[i]; 
			//calc sum y 
			sum_y += y[i]; 
			//calc sum x*x
			sum_x_square += x[i]*x[i]; 
			
		}
		//----LOOP REGION----
		gettimeofday(&t3, NULL); //end of timing of LOOP REGION
		
		//calc square of sum x
		square_sum_x = sum_x * sum_x; 	
		
		//plug in 'em all (as illustrated in https://www.mathsisfun.com/data/least-squares-regression.html)	
		m=(N*sum_xy - sum_x * sum_y)/(N*sum_x_square - square_sum_x);
		
		c=(sum_y - m*sum_x)/N;
		
		printf("<=> y=mx+c <=> y=%fx+%f \t",m,c);
		
		gettimeofday(&t4, NULL);	//end of timing	of WHOLE CODE
		
		double Secs = (t4.tv_sec - t1.tv_sec);           
		double t4_t1 = eps * ((Secs*1000000) + (t4.tv_usec - t1.tv_usec)); //calc WHOLE CODE
		Secs = (t3.tv_sec - t2.tv_sec);
		double t3_t2 = eps * ((Secs*1000000) + (t3.tv_usec - t2.tv_usec)); //calc LOOP REGION
		printf("Execution Time WHOLE CODE : %f seconds LOOP REGION : %f seconds \t", t4_t1, t3_t2);
	}

//function definition of 'f' for calculating y, as defined by assignment requirements.	
double f(double x){
	double y=1.0/exp(x/50000.1) + sin(x/501.1) / (log(x+eps)+cos(x/499.01+x));
	return y;
	}
