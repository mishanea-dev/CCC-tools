#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include <utility>
using namespace std;

ifstream fin("input.txt");
ofstream fout("out.txt");

#define cin fin
#define cout fout

const int safety_area = 3; 

bool isNegative = false;

int map_output(int x){
    if (x == 0) return 0;
    else x = 6-(x%6);

    if(isNegative) return x*-1; else return x;
}

vector<int> genMovement(int finish){
    vector<int> result;

    isNegative = false;
    int pace = 0;
    
    if(finish < 0) isNegative = true;
    finish = abs(finish);
    
    while(finish>0){
        result.push_back(map_output(pace));
        if (pace != 0) finish--;
        
        if(finish<pace) pace--;
        else if(finish>pace && pace < 5) pace++;
    } 
    result.push_back(0);

    return result;
}


int main()
{
    int n;
    int time; // usless, just for reading input
    char comma;
    pair<int, int> finish, asteroid;
    
    
    cin >> n; //cin.ignore();
    for(int _=0; _<n; _++){
        cin >> finish.first >> comma >> finish.second >> time;
        cin >> asteroid.first >> comma >> asteroid.second;

        // if asteroid is on x axis with the ship
        if( abs(finish.first - asteroid.first) >= safety_area &&
            abs(0 - asteroid.second) >= safety_area){

            vector<int> x_moves = genMovement(finish.first);
            vector<int> y_moves = genMovement(finish.second);

            
            int needed_zeros = 0;
            for(int i=0; i<x_moves.size(); i++){
                cout << x_moves[i] << ' ';
                needed_zeros+=abs(x_moves[i]);
            } cout << endl;

            while(needed_zeros > 0){
                cout << "0 ";
                needed_zeros--;
            }

            for(int i=0; i<y_moves.size(); i++){
                cout << y_moves[i] << ' ';
            }
            cout << endl;
        } else 
        // If asteroid is on y axis with the ship
        if( abs(finish.second - asteroid.second) >= safety_area &&
            abs(0 - asteroid.first) >= safety_area){

            vector<int> x_moves = genMovement(finish.first);
            vector<int> y_moves = genMovement(finish.second);

            int needed_zeros = 0;
            
            for(int i=0; i<y_moves.size(); i++){
                needed_zeros+=abs(y_moves[i]);
            }
            while(needed_zeros > 0){
                cout << "0 ";
                needed_zeros--;
            }

            for(int i=0; i<x_moves.size(); i++){
                cout << x_moves[i] << ' ';
                
            } cout << endl;

            

            for(int i=0; i<y_moves.size(); i++){
                cout << y_moves[i] << ' ';
            }
            cout << endl;
        } else
        // If asteroid is in between the ship and the station on x axis
        if( abs(finish.first - asteroid.first) >= safety_area &&
            abs(0 - asteroid.second) < safety_area){
            
            //move 3 units in y direction
            vector<int> y_moves = genMovement(abs(asteroid.second)+safety_area);

            //move all the way in x direction
            vector<int> x_moves = genMovement(finish.first);

            //move back 3 units in y direction
            vector<int> y_moves_back = genMovement(-1*(abs(asteroid.second)+safety_area) + finish.second);

            //print output:
            int needed_zeros = 0;
            for(int i=0; i<y_moves.size(); i++){
                needed_zeros+=abs(y_moves[i]);
            }
            int temp_needed_zeros = needed_zeros;
            while(temp_needed_zeros > 0){
                cout << "0 ";
                temp_needed_zeros--;
            }

            for(int i=0; i<x_moves.size(); i++){
                cout << x_moves[i] << ' ';
                needed_zeros+=abs(x_moves[i]);
            } cout << endl;

            for(int i=0; i<y_moves.size(); i++){
                cout << y_moves[i] << ' ';
            }
            while(needed_zeros > 0){
                cout << "0 ";
                needed_zeros--;
            }
            for(int i=0; i<y_moves_back.size(); i++){
                cout << y_moves_back[i] << ' ';
            } cout << endl;


        }
        else 
        // If asteroid is in between the ship and the station on y axis
        if( abs(finish.second - asteroid.second) >= safety_area &&
            abs(0 - asteroid.first) < safety_area){
            
            //move 3 units in x direction + station location
            vector<int> x_moves = genMovement(abs(asteroid.first)+safety_area);

            //move all the way in y direction
            vector<int> y_moves = genMovement(finish.second);
            //move back 3 units in y direction
            vector<int> x_moves_back = genMovement(-1*(abs(asteroid.first)+safety_area) + finish.first);
                
            //print output:
            int needed_zeros = 0;
            int needed_zeros_x = 0;
            for(int i=0; i<y_moves.size(); i++){
                needed_zeros+=abs(y_moves[i]);
            }
            for(int i=0; i<x_moves.size(); i++){
                needed_zeros_x+=abs(x_moves[i]);
            }

            for(int i=0; i<x_moves.size(); i++){
                cout << x_moves[i] << ' ';
            } 
            while(needed_zeros > 0){
                cout << "0 ";
                needed_zeros--;
            }
            for(int i=0; i<x_moves_back.size(); i++){
                cout << x_moves_back[i] << ' ';
            } cout << endl;

            while(needed_zeros_x > 0){
                cout << "0 ";
                needed_zeros_x--;
            }
            for(int i=0; i<y_moves.size(); i++){
                cout << y_moves[i] << ' ';
            } cout << endl;

            


        } else {
            cout << " --- IGNORE --- " << endl << endl;
        }
        
        


        cout << endl;

    }

    

    return 0;
}