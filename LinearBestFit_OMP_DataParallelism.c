#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 50000000	//set the number of points in quadrant
#define eps 1.0E-06	//set the computation tolerance, eps

//global vars of points
double x[N];
double y[N];

double f(double x);	//function declaration of 'f' for calculating y
int main(){
		double t1 = omp_get_wtime();	//begin timing of WHOLE CODE
		
		//----WHOLE CODE----
		double sum_xy=0, sum_x=0, sum_y=0, sum_x_square=0, square_sum_x=0, m=0, c=0;	 //declare vars for 'sums', m, and c coefficient 
		int i;	//for iteration
		
		double t2 = omp_get_wtime();	//start of timing of PARALLEL REGION	
			
		//----PARALLEL REGION----
		//create team of threads, using worksharing-loop construct.
		//we sum up all of the 'partial sums' variables from each thread into 'global sums' 
		#pragma omp parallel default(none) shared(x, y, sum_xy,sum_x,sum_y,sum_x_square) private(i) 
		#pragma omp for reduction(+:sum_xy,sum_x,sum_y,sum_x_square) 	schedule(static)
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
		//----PARALLEL REGION----
		
		double t3 = omp_get_wtime();	//end of timing	of PARALLEL REGION
		
		//calc square of sum x
		square_sum_x = sum_x * sum_x; 
			
		//plug in 'em all (as illustrated in https://www.mathsisfun.com/data/least-squares-regression.html)
		m=(N*sum_xy - sum_x * sum_y)/(N*sum_x_square - square_sum_x);
		
		c=(sum_y - m*sum_x)/N;
		
		printf("<=> y=mx+c <=> y=%fx+%f \t",m,c);
		
		double t4 = omp_get_wtime();	//end of timing	of WHOLE CODE
		
		printf("Execution Time WHOLE CODE : %f seconds PARALLEL REGION : %f seconds \t", t4-t1, t3-t2);
	}

//function definition of 'f' for calculating y, as defined by assignment requirements.	
double f(double x){
	double y=1.0/exp(x/50000.1) + sin(x/501.1) / (log(x+eps)+cos(x/499.01+x));
	return y;
	}
