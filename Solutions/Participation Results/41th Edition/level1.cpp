/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("out.txt");

#define cin fin
#define cout fout

int main()
{
    int n;
    string line;
    int number;
    char buffer;
 
    

    cin >> n; cin.ignore();
    for(int _=0; _<n; _++){
        long possition = 0;
        long time = 0;
        
        getline(cin, line);
        istringstream iss(line);
        
        while(iss >> number){
            if(number < 0) possition--;
            else if(number > 0) possition++;
            
            if(number == 0) time++; 
            else time+=abs(number);

        }
        cout << possition << ' ' << time << endl;
    }

    //cout.close();

    return 0;
}