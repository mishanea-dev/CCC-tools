#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("levels/level3_5.in");
ofstream fout("out.txt");

#define cin fin
#define cout fout

int main()
{
    int n, x, y, s;
    cin >> n;
    for(int i=0; i<n; i++){
        int id[] = {1, 0, 0};
        int max_id = 1;

        cin >> x >> y >> s;

        //setup all the id
        if(x%3 > 0){
            id[1]=max_id+1; max_id++;
            if(x%3>1){ id[2]=max_id+1; max_id++;}
        }

        
        for(int j=1; j<=y; j++){
            if(j > y-(y%3) && x%3>0){
                cout << 0 << ' ';
                if(x%3 > 1) cout << 0 << ' ';
            } else {
                for(int k=1; k<=x%3; k++){
                    cout << id[k] << ' ';
                    if(j%3 == 0 && j < y-(y%3)){
                        // if(max_id < s){
                            id[k]=max_id+1;
                            max_id++;
                        // } else {
                            // id[k]=0;
                        // }
                    }
                }
                
            }
            
            for(int k=1; k<=x/3; k++){
                for(int a=0; a<3; a++){
                    cout << id[0] << ' ';
                } 
                // if(max_id < s){
                    id[0]=max_id+1; 
                    max_id++;
                // } else {
                //     id[0] = 0;
                // }
            }
        // cout << '[' << id[1] << ']';
            cout << endl;
        }

        
        cout << endl;
    }
    
    return 0;
}

/*
3
7 5 11
8 5 11
8 8 11

*/