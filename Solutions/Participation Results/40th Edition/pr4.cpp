#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("levels/level4_5.in");
ofstream fout("out.txt");

#define cin fin
#define cout fout

bool checkNeighbors(vector<vector<int>> &t, int x, int y, int ignore = 0){ //ignore 0-none, 1-up, 2-down, 3-right, 4-left
    if(t[y+1][x]!=0 && ignore!=1) return false;
    if(t[y-1][x]!=0 && ignore!=2) return false;
    if(t[y][x+1]!=0 && ignore!=3) return false;
    if(t[y][x-1]!=0 && ignore!=4) return false;
    if(t[y+1][x+1]!=0) return false;
    if(t[y+1][x-1]!=0) return false;
    if(t[y-1][x+1]!=0 ) return false;
    if(t[y-1][x-1]!=0) return false;
    return true;
}

void addTable(vector<vector<int>> &t, int x, int y, int length = 3){
    bool vertical = true, horizontal = true;
    
// cout << "[" << t.size() << ' ' << t[0].size() << ']';

    //vertical table
    for(int i=0; i<length; i++){
        if(y+i > t.size()-2) { vertical=false; break;} else
        if(!checkNeighbors(t, x, y+i)) vertical = false;
    }
    if(vertical){
        for(int i=0; i<length; i++){
            t[y+i][x] = 1;
        }
        return;
    }
    
    //horizontal table
    for(int i=0; i<length; i++){
        if(x+i > t[0].size()-2) return; else
        if(!checkNeighbors(t, x+i, y)) horizontal = false;
    }
    if(horizontal){
        for(int i=0; i<length; i++){
            t[y][x+i] = 1;
        }
        return;
    }

    return;
}

void room(){
    int x, y, s;
    cin >> x >> y >> s;
    vector<vector<int>> t(y+2, vector<int>(x+2, 0));

    for(int i=1; i<=y; i++){
        for(int j=1; j<=x; j++){
            addTable(t, j, i);
        }
    }
    
    
    for(int i=1; i<=y; i++){
        for(int j=1; j<=x; j++){
            if(t[i][j]==1) cout << "X";
            else cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        room();
    }
    // room();
    
    return 0;
}