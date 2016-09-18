/* This program was made for Project 1 in the course
 * FYS3150 - Computational Physics. Enjoy. */

#include <cmath>        //For math
#include <iostream>     //For printing with cout
#include <fstream>      //For file read
#include <algorithm>    //For filling arrays
#include <ctime>        //For calculating run time
#include <string>       //For string operations
#include <armadillo>    //For LU composition

using namespace std;
using namespace arma;

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

void special_solver(int N, double h){
    double *A = new double[N];
    double *d = new double[N];
    double *u = new double[N];
    A[0] = 2;
    for(int i = 0; i < N; i++){
        double x = (i+1)*h;
        d[i]=pow(h,2)*func(x);
    }
    for(int i = 1; i < N; i++){
        A[i]=(i+2.)/(i+1);
        d[i]=d[i]+d[i-1]/A[i-1];
    }
    u[N-1]=d[N-1]/A[N-1];               //Set initial conditions for u
    ofstream infile;                    //Giving the file representation name
    infile.open("second_der.dat");         //Connecting name to file
    infile << 0 << " " << 0 << endl;    //Boundary conditions

    for(int i = N-2; i >= 0; i--){
        u[i]=(d[i]+u[i+1])/A[i];
    }
    for(int i=0; i<N; i++) {
        double x = (i+1)*h;
        infile << u[i] << "    " << exact(x) << endl;
    }

    infile << 0 << " " << 0 << endl;    //Set boundary conditions
    infile.close();
}

void general_solver(int N, double h){
    double *d = new double[N];
    double *u = new double[N];
    double *A = new double[N];
    int *B = new int[N-1];
    int *C = new int[N-1];

    //Array operations
    fill_n(A,N,2);                      //Fill array a with 2s
    fill_n(B,N-1,-1);                   //Fill array b with -1s
    fill_n(C,N-1,-1);                   //Fill array c with -1s

    //Interation loops to fill the arrays
    for(int i = 0; i < N; i++){
        double x = (i+1)*(h);
        d[i]=pow(h,2)*func(x);       //Filling f
    }
    for(int i = 1; i < N; i++){
        A[i]=A[i]-B[i-1]*(C[i-1]/A[i-1]);
        d[i]=d[i]-d[i-1]*(C[i-1]/A[i-1]);
    }

    //Set initial conditions for u
    u[N-1]=d[N-1]/A[N-1];
    ofstream infile;                    //Giving the file representation name
    infile.open("second_der.dat");         //Connecting name to file
    infile << 0 << " " << 0 << endl;
    for(int i = N-2; i >= 0; i--){
        u[i]=(d[i]-B[i]*u[i+1])/A[i];

    }
    for(int i = 0; i < N; i++){
        double x = (i+1)*h;
        infile << u[i] << "    " << exact(x) << endl;
    }
    infile.close();
}

void LU_decomposition(int N, double h){
    mat A = zeros<mat>(N,N), P, L, U;
    vec d = zeros<vec>(N), u;

    // Filling A
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i==j){
                A(i,j)=2;
            }
            if((i-1)==j){
                A(i,j)=-1;
            }
            if((i+1)==j){
                A(i,j)=-1;
            }
        }
    }

    //Filling f
    for(int i = 1; i < N; i++){
        double k = i*h;
        d(i)=pow(h,2)*func(k);
    }
    //Decomposition
    lu(L,U,P,A);                        // Computing L and U
    u = solve(trimatu(U), solve(trimatl(L),P*d));

    //Writing to file
    ofstream infile;
    infile << 0 << " " << 0 << endl;
    infile.open("second_der.dat");
    for(int i = 0; i < N; i++){
        double x = i*h;
        infile << u[i] << "    " << exact(x) << endl;
    }
    infile.close();
}

int main (int argc,char *argv[])
{
    //Constants
    if(argc == 1) {
        cout << "Error: Need to set N as command line element" << endl;
        exit(1);
    }
    int N = atoi(argv[1]);                      // Number of iterations
    double h = 1./(N+1);                        // Step length

    // Declare start and final time
    clock_t start, finish;
    start = clock();

    //general_solver(N,h);
    special_solver(N,h);
    //LU_decomposition(N,h);

    finish = clock();
    cout << N << endl;
    cout << "Run time: " << (finish-start)/float(CLOCKS_PER_SEC) << "s" << endl;
    return 0;
}
