#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
 
/*
This code solve a 1D heat equation with diriclet boundary conditions.
 
    PDE: u_t = u_xx
    Boundary conditions: u(0) = u(1) = 0
    Initial conditions: u(x,0) = 1
 
An explicit finitie difference scheme (FTCS - forward time centred space):
 
    u_(i+1,j) = u_(i,j) + R * (u_(i,j+1)-2*u_(i,j)+u_(i,j-1)) 
 
where, 
 
    i:      time discretization indecies
    j:      spatial discretization indecies
    del_x:  x_i+1 - x_i
    del_t:  t_i+1 - t_i
    R:      k*del_t/del_x^2  
 
The solution is saved as results.csv. 
 
*/
 
int main(){
 
    // Setting PDE and discretization parameters
    // ---------------------------------------------------------------
    double k;
    cout << "\nThermal conductivity (k) = "; cin >> k;
    int n,m;
    cout << "\nNumber of grid points: "; cin >> n;
    double del_x = 1/(double(n)-1);
    cout << "\nSpatial step size (del_x) = " << del_x << endl;
    cout << "\nNumber of time steps: "; cin >> m;
    double del_t;
    cout << "\nTime step size (del_t) = "; cin >> del_t; cout;
    double R = k*(del_t/pow(del_x,2));      // Courant number
    cout << "\nR = " << R << endl << endl;  // For FTCS this must be =< 1/2 for stable solution
 
    // Constructing initial condition vector and x-coordinate vector
    // ---------------------------------------------------------------
    vector<double> x,u;
    for(int j=0; j<n; j++){
        x.push_back(j*del_x);
        u.push_back(1);
    }
 
    // An explicit (FTCS) scheme for solving u_t = u_xx
    // ---------------------------------------------------------------
    ofstream fout;
    fout.open("results.csv");
    fout << "x," << "t," << "u" << "\n";                // Print headers in results file
 
    for (int j=0; j<n; j++)
    fout << x[j] << "," << 0 << "," << u[j] << "\n";    // print initial condition results in file 
 
    for(int i=0; i<m; i++){                              // time stepping 
 
        u[0]=0;                                         // setting boundary condition at u(0)
        for(int j=1; j<(n-1); j++){                  
 
            u[j]= u[j] + R*(u[j+1]-2*u[j]+u[j-1]);      // Forward time centred space difference scheme
        }
        u[n-1]=0;                                       // setting boundary condition at u(1)
 
        for (int j=0; j<n; j++)
        fout << x[j] << "," << (i+1)*del_t << "," << u[j] << "\n";
    }
 
    fout.close();
 
    // Print last time step results on terminal
    // ---------------------------------------------------------------
    cout << "Results from last time step u(x," << m*del_t << "): \n\n";
    cout << setprecision(3) << setw(5) << "x[j]" << "\t" << setprecision(3) << setw(5) << "u[j] \n\n";
    for(int j=0; j<x.size(); j++){
            cout << setprecision(3) << setw(5) << x[j] << "\t" << setprecision(3) << setw(5) << u[j]<< endl;
    }
 
    return 0;
}