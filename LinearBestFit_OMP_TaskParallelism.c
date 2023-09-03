#include <stdio.h>
#include <math.h>
#include <omp.h>

#define N 50000000	//set the number of points in quadrant
#define eps 1.0E-06	//set the computation tolerance, eps

#define MIN_PART 500 //define partition of binary tree recursion

double f(double x); //function declaration of 'f' for calculating y
void splitSums(int start,int finish,double *sum_xy,double *sum_x,double *sum_y,double *sum_x_square); //function declaration for 'recursive' calculation of 'sums' (we define 'sums' as the vars of sum_xy,sum_x,sum_y,sum_x_square)
int main(){
		double t1 = omp_get_wtime();	//begin timing of WHOLE CODE
		
		//----WHOLE CODE----
		double sum_xy=0, sum_x=0, sum_y=0, sum_x_square=0, square_sum_x=0, m=0, c=0; //declare vars for 'sums', m, and c coefficient 
		
		double t2 = omp_get_wtime();	//start of timing of PARALLEL REGION	
			
		//----PARALLEL REGION----
		#pragma omp parallel	//create team of threads
		{
			#pragma omp single	//one thread create the recursive function
			{
				//calling splitSums function. The 'sums' parameters are passed by their reference.
				splitSums(0,N,&sum_xy,&sum_x,&sum_y,&sum_x_square); 
			}
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

/*function definition for 'recursive' calculation of 'sums' (we define 'sums' as the vars of sum_xy,sum_x,sum_y,sum_x_square)
 * The 'sums' parameters are passed by their reference.
 * parameter 'start' and 'finish' are for determining the segment of recursion.
 * this function will imitate 'binary tree' recursion, where we split the problem into two parts and divide again the split problem in recursive mannner
 * each of split problem will be assigned as a task
 * 'partial sums' : sum_xy1, sum_xy2, sum_x1, sum_x2, sum_y1,  sum_y2, sum_x_square1, sum_x_square2;
 * 'global sums' : *sum_xy, *sum_x, *sum_y, *sum_x_square
*/ 
void splitSums(int start,int finish,double *sum_xy,double *sum_x,double *sum_y,double *sum_x_square){
	int i, ipart;
	double x,y;
	//initialise the 'partial sums'
	double sum_xy1=0, sum_xy2=0, sum_x1=0, sum_x2=0, sum_y1=0,  sum_y2=0, sum_x_square1=0, sum_x_square2=0;
	//printf("Hi I'm thread=%d, start=%d, finish=%d \n",omp_get_thread_num(),start,finish);	//debug only
	if (finish-start < MIN_PART){	
		for(i=start;i<finish;i++){
			x=i/1003.01;
			y=f(x);
			//calc sum xy
			*sum_xy += x*y;
			//calc sum x
			*sum_x += x; 
			//calc sum y 
			*sum_y += y; 
			//calc sum x*x
			*sum_x_square += x*x; 
		}
	}else{
		ipart = finish-start;	//define the length of segment of recursion
		#pragma omp task shared(sum_xy1,sum_x1,sum_y1,sum_x_square1)	//define a queue of task, where 'partial sums' declared as shared variable
		splitSums(start,finish-ipart/2,&sum_xy1,&sum_x1,&sum_y1,&sum_x_square1);	//this function will modify the values of 'global sums'
		#pragma omp task shared(sum_xy2,sum_x2,sum_y2,sum_x_square2)	//define a queue of task, where 'partial sums' declared as shared variable
		splitSums(finish-ipart/2,finish,&sum_xy2,&sum_x2,&sum_y2,&sum_x_square2);	//this function will modify the values of 'global sums'
		#pragma omp taskwait	//all threads will need to wait before proceed to the summation 
		//sum the 'partial sums' into 'global sums'
		//since we use the pointer, we will modify directly the values of 'global sums'
		*sum_xy = sum_xy1+sum_xy2;
		*sum_x = sum_x1+sum_x2;
		*sum_y = sum_y1+sum_y2;
		*sum_x_square = sum_x_square1+sum_x_square2;
	}
}
