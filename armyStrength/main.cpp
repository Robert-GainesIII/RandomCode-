#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

void trial(list<int> &, list<int> &);
void battle(list<int> &, list<int> &);

int main(){

 int trials;
 int godzillaSize;
 int megaGodzillaSize;

 cin >> trials;

 list<int> armyGodzilla;
 list<int> armyMegaGodzilla;

 int value;

for(int i = 0; i < trials; i++){
    
     cin >> godzillaSize;
     cin >> megaGodzillaSize;

    
    for(int i = 0; i < godzillaSize; i++){
        
        cin >> value;
        armyGodzilla.push_back(value);
    }
    for(int i = 0; i < megaGodzillaSize; i++){
        cin >> value;
        armyMegaGodzilla.push_back(value);
    }

    trial(armyGodzilla,armyMegaGodzilla);

    armyGodzilla.clear();
    armyMegaGodzilla.clear();
} 

 return 0;   
}

void trial(list<int> & godzilla,list<int> &  megaGodzilla){
   //cout << size1 << endl;
   //cout << size2 << endl;
   while(godzilla.size() > 0 && megaGodzilla.size() > 0){
       battle(godzilla, megaGodzilla);
   }
   if(godzilla.size() == 0)cout << "MegaGodzilla" << endl;
   else if(megaGodzilla.size() == 0)cout << "Godzilla" << endl;
   else cout << "undetermined" << endl;
}

void battle(list<int> & godzilla,list<int> &  megaGodzilla){
    int weakestA1 = 10000;
    int weakestA2 = 10000;
    vector<int> weakestA1Index;
    vector<int> weakestA2Index;
    list<int>::iterator it;
    int count = 0;

    //CHECK FOR WEAKEST AND CREATE A LIST OF ALL THE WEAKEST WITH SAME LEVEL
    for(it = godzilla.begin(); it != godzilla.end(); it++){
        if(*it < weakestA1)weakestA1 = *it;
    }
    for(it = godzilla.begin(); it != godzilla.end(); it++){
        if(*it == weakestA1)weakestA1Index.push_back(count); 
        count++;
    }
    count = 0; //RESET COUNTER
    for(it = megaGodzilla.begin(); it != megaGodzilla.end(); it++){
        if(*it < weakestA2)weakestA2 = *it;
    }
    for(it = megaGodzilla.begin(); it != megaGodzilla.end(); it++){
        if(*it == weakestA2)weakestA2Index.push_back(count); 
        count++;
    }

    if(weakestA1 == weakestA2){

        int range = weakestA2Index.size();
        if(range > 1){
            int randomDelete = rand() % range;
            int selected = weakestA2Index.at(randomDelete);
            megaGodzilla.remove(selected);
        }
        else{
            megaGodzilla.pop_back();

        }
    }
    else if(weakestA2 < weakestA1){
        int range = weakestA2Index.size();
        if(range > 1){
            int randomDelete = rand() % range;
            int selected = weakestA2Index.at(randomDelete);
            megaGodzilla.remove(selected);
        }
        else{
            megaGodzilla.pop_back();
        }
    }
    else if(weakestA1 < weakestA2){
        int range = weakestA1Index.size();
        if(range > 1){
            int randomDelete = rand() % range;
            int selected = weakestA1Index.at(randomDelete);
            godzilla.remove(selected);
        }
        else{
            godzilla.pop_back();
        }
    }
    else{
        cout << "HUH?" << endl;
    }
}