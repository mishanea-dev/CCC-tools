#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream fin("levels/level5_1.in");
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

bool addTableV(vector<vector<int>> &t, int x, int y, int length = 2){
    bool vertical = true;

    for(int i=0; i<length; i++){
        if(y+i > t.size()-2) return false; else
        if(!checkNeighbors(t, x, y+i)) vertical = false;
    }
    if(vertical){
        for(int i=0; i<length; i++){
            t[y+i][x] = 1;
        }
        return true;
    }
    
    return false;
}
bool addTableH(vector<vector<int>> &t, int x, int y, int length = 2){
    bool horizontal = true;

    for(int i=0; i<length; i++){
        if(x+i > t[0].size()-2) return false; else
        if(!checkNeighbors(t, x+i, y)) horizontal = false;
    }
    if(horizontal){
        for(int i=0; i<length; i++){
            t[y][x+i] = 1;
        }
        return true;
    }

    return false;
}

// vector<vector<int>> search(vector<vector<int>> t = , int x, int y){

// }

void room(){
    int x, y, s;
    cin >> x >> y >> s;
    vector<vector<int>> tt;
    
    int choice[s];
    for(int i=0; i<s; i++) choice[i]=0;

    int count;

    // [&]{
        while(count>0){
            vector<vector<int>> t(y+2, vector<int>(x+2, 0));

            count = s;
            int ord = 0;

            for(int i=1; i<=y; i++){
                for(int j=1; j<=x; j++){
                    if(choice[ord] == 1){
                        if(addTableV(t,x,y)){
                            ord++;
                            count--;
                        }
                    } else {

                    }
                }
            }
            
            //pick another choice
            for(int i=0; i<s; i++){
                if(choice[i]<1){
                    choice[i]++;
                    break;
                } else {
                    int x = i;
                    while(choice[x]==1){
                        choice[x]=0;
                        x++;
                    }
                    choice[x]++;
                }
            }
            if(count==0) tt=t;
        }    
    // }();
    
    
    for(int i=1; i<=y; i++){
        for(int j=1; j<=x; j++){
            if(tt[i][j]==1) cout << "X";
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
        // room();
    }
    room();
    
    return 0;
}