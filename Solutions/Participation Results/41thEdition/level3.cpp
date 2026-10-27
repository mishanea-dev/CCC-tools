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

bool isNegative = false;

int map_output(int x){
    if (x == 0) return 0;
    else x = 6-(x%6);

    if(isNegative) return x*-1; else return x;
}

int main()
{
    int n;
    //string line;
    
    int finish;
    int time;
    

 
    

    cin >> n; //cin.ignore();
    for(int _=0; _<n; _++){
        cin >> finish >> time;
        
        isNegative = false;
        int pace = 0;
        
        if(finish < 0) isNegative = true;
        finish = abs(finish);
        
        while(finish>0){
            cout << map_output(pace) << ' ';
            if (pace != 0) finish--;
            
            if(finish<pace) pace--;
            else if(finish>pace && pace < 5) pace++;
            //cout << "DEBUG{" << pace << "}\n";
        
        }

        cout << "0\n";
    }

    

    return 0;
}