/* This is the program for the warmup
exercises given in the start of the
semester */

#include <cmath>        //For math
#include <iostream>     //For printing with cout
#include <fstream>      //For file read
#include <iomanip>      //For digit precision
#include <vector>       //For vectors
//#include <chplot.h>

using namespace std;

double f (double a)
/* This is a function f which takes
 * a float number 'a' as argument
 * and returns arctan 'a' */
{
    double r;
    r=atan(a);
    return r;
}

double derivation1 (double x, double h)
/* This function calculates the
 * derivated of the function f in
 * the point 'x' with 'h' steplength
 * by Forward-Euler */
{
    double r;
    r=(f(x+h)-f(x))/h;
    return r;
}

double derivation2 (double x, double h)
/* This function calculates the
 * derivated of the function f in
 * the point 'x' with 'h' steplength
 * by the 3-Point method */
{
    double r;
    r=(f(x+h)-f(x-h))/(2*h);
    return r;
}

int main ()
{
    double z1; double z2;                       //Variables for storing the derivated
    double h = 10^-6;
    ofstream der1file; ofstream der2file;       //Naming the file representation
    der1file.open("derivation1.txt");           //Connecting name to file
    der1file << "h      derivation value\n";    //Writing head line in file
    der2file.open("derivation2.txt");
    der2file << "h      derivation value\n";

    for(h; h > 0.00000000001; h = h - 0.00000000001)
    /* This for loop counts from 10^-6 to 10^-11 with timestep 10^-11
     * I prefer to make h smaller and smaller because I want to see
     * the error sink. */
    {
        z1 = derivation1(sqrt(2),h);
        z2 = derivation2(sqrt(2),h);
        der1file << h << "  " << std::setprecision(10) << z1 << endl;
        der2file << h << "  " << std::setprecision(10) << z2 << endl;
    }
    der2file.close();       //Closing the file
    der1file.close();
    cout << "The relative error is " << fabs(z1-1/3.) << " for method 1" << endl;
    cout << "and " << fabs(z2-1/3.) << " for method 2" << endl;  //Prints relative error

    ifstream infile;
    infile.open("derivation1.txt");
    infile >> data;         // Reading from the file
    cout << data << endl;   // Write the data at the screen.

    // again read the data from the file and display it.
    infile >> data;
    cout << data << endl;

    infile >> data;
    cout << data << endl;

    // close the opened file.
    infile.close();
    return 0;
}
