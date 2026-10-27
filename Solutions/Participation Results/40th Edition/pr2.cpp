#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("level2_5.in");
ofstream fout("out.txt");

#define cin fin
#define cout fout

int main()
{
    int n, x, y, s;
    cin >> n;
    for(int i=0; i<n; i++){
        int id=1;
        cin >> x >> y >> s;
        for(int k=1; k<=y; k++){
            for(int j=0; j<x/3; j++){
                for(int a=0; a<3; a++){
                    cout << id << ' ';
                } 
                id++;
            }
            cout << endl;
        }
        cout << endl;
    }

    
    
    return 0;
}