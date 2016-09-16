/*
 *	Name: Adriani Furtado
 *	Student ID: 1389795
 *
 *	Benchmark code - for
 *	the EECT615 coursework assignment, 2015-2016
 */

#include <sys/time.h>
#include <stdio.h>

#define MAXLEN 600000	//Maximum Variable Lenght
#define	N_ITT 1000	//Number of Itterations
#define STRIDER 5	//Size of Strides

main(){
	static double x[MAXLEN] , y[MAXLEN];
	double a = 2.0;
	int i, j, vlen;
	struct timeval timev;
	double t1, t2, t1s,t2s;

	//Initializing Values inside of the array spaces
	for(i = 0; i < MAXLEN ; i++){
	
		x[i] = 1.00;
		y[i] = 0.00;

	}
	
	//Loop for effective array size incrementation 
	for(vlen = 1; vlen < MAXLEN ; vlen *= 2){

	        //************** Unit Stride DAXPY Loop Begin	
		//storing current time inside the first timer variable
		gettimeofday(&timev,NULL);
		t1 = (double)(timev.tv_sec+timev.tv_usec*1.0e-6);

		//Loop used for the number of itterations(repetitions).
		for(j=0;j<N_ITT; j++){
		
			//Unit Stride Daxpy loop
			for(i=0;i<vlen; i++){
		
				y[i] += a * x[i] ; //DAXPY Double precission a*x+y

			}

		}
	
		//storing time inside second timer variable
		gettimeofday(&timev,NULL);
                t2 = (double)(timev.tv_sec+timev.tv_usec*1.0e-6);		
		//************** Unit Stride DAXPY Loop End

		//************** Strided DAXPY Loop Begin
		//Storing time
		gettimeofday(&timev,NULL);
                t1s = (double)(timev.tv_sec+timev.tv_usec*1.0e-6);
		
		//Loop for number of itterations
		for(j=0;j<N_ITT; j++){

			//Strided Daxpy loop
                        for(i = 0; i<vlen;i++ ){

                                y[(i * STRIDER)%vlen] += a * x[(i * STRIDER)%vlen] ; //DAXPY Double precission a*x+y
			}

                }

		//Storing time
		gettimeofday(&timev,NULL);
                t2s = (double)(timev.tv_sec+timev.tv_usec*1.0e-6);
		//************** Strided Loop End

		//Calculations
		int array_size = vlen * 8;	//effective array size * size of double(8)
		double U_time = (double)((t2-t1)*1.0e6)/N_ITT;	//Unit Stride: Time2 - Time1 / Number of itterations for individual daxpy time
		double S_time = (double)((t2s-t1s)*1.0e6)/N_ITT;	//Strided: Time2 - Time1 / Number of itterations for individual daxpy time
		double U_mflops = (2*N_ITT*vlen) / ((t2-t1) * 1.0e6);	//(2*number of itterations * Effective array size) / (Timer2-Timer1 * 10^6) for MFLOPS
		double S_mflops = (2*N_ITT*vlen) / ((t2s-t1s) * 1.0e6);	// Same formula as stated above
		//*******

		//Printing in the following format: Effective Size ; Unit Stride DAXPY; Unit Stride MFLOPs; Strided time; Strided MFLOPs
		printf("%d \t %4.3lfus\t %4.3lf MFLOPs\t %4.3lfus\t %4.3lf MFLOPs \n", array_size, U_time, U_mflops , S_time , S_mflops );
	}
}
