/* I made this program for Project 1 in the course
 * FYS3150 - Computational Physics. Enjoy. */

#include <cmath>        //For math
#include <iostream>     //For printing with cout
#include <fstream>      //For file read
#include <algorithm>    //For filling arrays
#include <ctime>        //For calculating run time
#include <string>       //For string operations

using namespace std;

double func (double x)
/* This is a function which takes
 * a float number 'x' as argument
 * and returns f(x)=100e^-10x */{
    double r;
    r = 100*exp(-10*x);
    return r;
}

double exact(double x)
/* This is the analytical solution
 * of the derivate of the function
 * above */{
    double r;
    r = 1-(1-exp(-10))*x-exp(-10*x);
    return r;
}

void u_to_file(double *f, double *A, double h, int N){
/* This function is solving U and writing the
 * array out to a file with the exact solution */
    double *u = new double[N];
    u[N-2]=f[N-2]/A[N-2];     //Set initial conditions for u
    u[N-1]=0;
    u[0]=0;
    ofstream infile;                    //Giving the file representation name
    infile.open("doubder.dat");         //Connecting name to file
    for(int j = N-3; j > 0; j -= 1){
        double k = j*h;
        u[j]=(f[j]+u[j+1])/A[j];
        infile << u[j] << "    " << exact(k) << endl;
    }
    infile.close();
}

void special_solver(int N, double h){
    double *A = new double[N];
    double *f = new double[N];
    A[0] = 2;
    f[0] = 0;
    for(int i = 1; i < N; i++){
        double k = i*h;
        f[i]=pow(h,2)*func(k);
        A[i]=(i+2.)/(i+1);
        f[i]=f[i]+f[i-1]/A[i-1];
    }
    u_to_file(f,A,h,N);
}

void general_solver(int N, double h){
    double *f = new double[N];
    double *A = new double[N];
    int *B = new int[N-1];
    int *C = new int[N-1];
    f[0]=0;

    //Array operations
    fill_n(A,N,2);                      //Fill array a with 2s
    fill_n(B,N-1,-1);                   //Fill array b with -1s
    fill_n(C,N-1,-1);                   //Fill array c with -1s

    //Interation loops to fill the arrays
    for(int i = 1; i < N+1; i += 1){
        double k = i*(h);
        f[i]=pow(h,2)*func(k);       //Filling f
        A[i]=A[i]-B[i-1]*(C[i-1]/A[i-1]);
        f[i]=f[i]-f[i-1]*(C[i-1]/A[i-1]);
    }
    u_to_file(f,A,h,N);
}

int main ()
{
    //Constants
    int N = pow(10,2);                          // Number of iterations
    double h = 1./(N+1);                        // Step length

    // Declare start and final time
    clock_t start, finish;
    start = clock();

    //general_solver(N,h);                      // For sub exercise b
    special_solver(N,h);                      // For sub exercise c

    finish = clock();
    cout << "Run time: " << (finish-start)/float(CLOCKS_PER_SEC) << "s" << endl;
    return 0;
}
