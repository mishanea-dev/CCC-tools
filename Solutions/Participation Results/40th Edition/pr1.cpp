#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("level2_1.in");
ofstream fout("out.txt");

#define cin fin
#define cout fout

int main()
{
    int s=0;
    int n, x, y;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> x >> y;
        cout << (x/3)*y << endl;

    }

    
    
    return 0;
}