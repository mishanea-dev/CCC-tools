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
    char comma;
    
    

    cin >> n; //cin.ignore();
    for(int _=0; _<n; _++){
        int finish_x;
        int finish_y;
        int time;
        cin >> finish_x >> comma >> finish_y >> time;


        isNegative = false;
        int pace = 0;
        
        if(finish_x < 0) isNegative = true;
        finish_x = abs(finish_x);
        
        while(finish_x>0){
            cout << map_output(pace) << ' ';
            if (pace != 0) finish_x--;
            
            if(finish_x<pace) pace--;
            else if(finish_x>pace && pace < 5) pace++;
            //cout << "DEBUG{" << pace << "}\n";
        
        }
        cout << "0\n";



        


        isNegative = false;
        pace = 0;
        
        if(finish_y < 0) isNegative = true;
        finish_y = abs(finish_y);
        
        while(finish_y>0){
            cout << map_output(pace) << ' ';
            if (pace != 0) finish_y--;
            
            if(finish_y<pace) pace--;
            else if(finish_y>pace && pace < 5) pace++;
            //cout << "DEBUG{" << pace << "}\n";
        
        }

        cout << "0\n\n";
    }

    

    return 0;
}