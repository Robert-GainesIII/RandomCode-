//--------------------------------------------------------------------------//
//File Name: main.cpp
//Project Name: Serendipity
//--------------------------------------------------------------------------//
//Creator's name and email: Robert Gaines, gaines.robert.edgar@gmail.com
//Course-Selection: CS 1A Ticket # 80600
//Creation Date: 1/28/19
//Date of Last Modification: 2/06/19
//--------------------------------------------------------------------------//
//Purpose: Working with file input and output while concreting lecture
//			Material about structs
//--------------------------------------------------------------------------//
//Algorithm: 
//Step 1: Main Loop (1-4) Menu navigtion until termination
//--------------------------------------------------------------------------//
//-							Data Dictonary
//- CONSTANTS 
// globalFlag used for printTeam formatting
//-
// VARIABLES
//
// NAME						DATA TYPE			INITIAL VALUE
// ----						---------			-------------  
//playerTypee 				struct				null				//
//TEAM_SIZE					int 				10 						//



#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string.h>
#include <ctype.h>

using namespace std;

bool globalFlag = false;

struct playerType {
	string name; 
	string position; 
	int numOfTD;
	int numOfCatches;
	int numPassYards;
	int numReceivingYards;
	int numRushYards;

};

const int TEAM_SIZE = 10;

void readFile(playerType (&team)[TEAM_SIZE], ifstream &fin);
void writeFile(playerType (&team)[TEAM_SIZE]);
void printPlayer(playerType player);
void printTeam(playerType (&team)[TEAM_SIZE]);
int  lookUpPlayer(playerType (&team)[TEAM_SIZE]);
void editPlayer(playerType (&team)[TEAM_SIZE]);


int main(){

	playerType team[TEAM_SIZE];
	ifstream fin;
	int index;
	fin.open("data.txt");
	if (fin) {
		readFile(team, fin);
		char choice = ' ';
		char c;
        while(choice != '4'){
			choice = ' ';
            system("cls");
            cout <<"*******************************"<<endl;
            cout <<"* <1>Look Up Player            *"<<endl;
            cout <<"* <2>Edit A  Player            *"<<endl;
            cout <<"* <3>Print Team Roster         *"<<endl;
            cout <<"* <4>Quit                      *"<<endl;
            cout <<"*******************************"<<endl;
            cout <<"* Choice (1-4): ";
            cin >> choice;
            switch(choice){
                case '1':
					index = lookUpPlayer(team);
						if(index>=0)printPlayer(team[index]);
						else cout << "Player Not Found!" << endl;
						globalFlag= false;
					system("pause");
                    break;
                case '2':
					editPlayer(team);
                    break;
                case '3':
				    printTeam(team);
                    break;
				case '4': 
				    cout << "Would you like to save this data?(Y/N)" << endl; 
					cin >> c;
					if(c == 'Y'){
						cout << "Saving Program" <<endl;
						writeFile(team);
					}
					cout<< "Exiting Program.." << endl;
					break;
                default:
                    cout << "Enter Valid Input (1-4)";
            }
        }
		fin.close();
	}
	else {
		cout << "File not found";
		return -1;
	}
    
	return 0; 
}

void readFile(playerType (&team)[TEAM_SIZE], ifstream &fin) {
	for (int i = 0; i < TEAM_SIZE; i++) {
		getline(fin, team[i].name);
        fin >> team[i].position;
        fin >> team[i].numOfTD;
        fin >> team[i].numOfCatches;
        fin >> team[i].numPassYards;
        fin >> team[i].numReceivingYards;
        fin >> team[i].numRushYards;
        fin.ignore(100,'\n');
	}
}

void printPlayer(playerType player){
		if(globalFlag != true)
		cout<< setw(20) << left << "Name" << setw(10) << "Pos" << setw(10) << "TDs" << setw(10) << "Catches" << setw(10) <<"PassYards" << setw(15) << "ReceivYards" << setw(15) << "RushYards" <<endl;
		globalFlag = true;
		cout<< setw(80) << setfill('-') << '-' << endl;
		cout<< setw(20) << setfill(' ') << player.name << setw(10) <<player.position<< setw(10) <<player.numOfTD <<setw(10) <<player.numOfCatches << setw(15) <<player.numPassYards << setw(15) <<player.numReceivingYards << setw(15) << player.numRushYards << endl;
		cout<< setw(80) << setfill('-') << '-' << endl;
}

void printTeam(playerType (&team)[TEAM_SIZE]){
    for(int i =0; i < TEAM_SIZE; i++){
        printPlayer(team[i]);
    }
	system("pause");
	globalFlag = false;
}

int  lookUpPlayer(playerType (&team)[TEAM_SIZE]){
    int found = -1;
	int numOfMatches = 0;
    cout << endl << endl << "* Search: ";
    char answer[30];
    cin >> answer;
	
	
	//LOOP THROUGH TEAM ARRAY AND THEN LOOP THROUGH EACH LETTER OF INPUT AND COMPARE TO EACH PLAYERS NAME
	//PLAYER NAME WITH THE MOST MATCHING LETTERS IN A ROW WILL BE RETURNED
	for(int i = 0; i < TEAM_SIZE; i ++){
		
		if(team[i].name ==  string(answer)){
			return i;
		}
		char playerName[team[i].name.size() +1];
		strcpy(playerName, team[i].name.c_str());
		
		int count = 0;
		int x = 0;
		
			while(answer[x] != '\0'){
				
			//cout << answer[x] << " Compared to " << playerName[x];
			
			char a = toupper(playerName[x]);
			char b = toupper(answer[x]);
			int cmp = (a==b);
			
			//cout << " = " << cmp << endl;
			if(cmp == 1)count++;
			x++;
			if((count > numOfMatches) && count > 1){
				numOfMatches = count;
				found = i;
			}
			}
			
	}
    return found;
}

void editPlayer(playerType (&team)[TEAM_SIZE]){
	int index = lookUpPlayer(team);
    if(index>=0){
		char choice = ' ';
		while(choice != '8'){
			system("cls");
			cout<<" A5 Structs: Edit Player *"<<endl;
			cout<<"**************************"<<endl;
			cout<<"* <1>Player Name:        :"<<team[index].name << endl;
			cout<<"* <2>Position:           :"<<team[index].position<< endl;
			cout<<"* <3># of TouchDowns:    :"<<team[index].numOfTD <<endl;
			cout<<"* <4># of Catches:       :"<<team[index].numOfCatches << endl;
			cout<<"* <5>Passing Yards:      :"<<team[index].numPassYards << endl;
			cout<<"* <6>Receiving Yards:    :"<<team[index].numReceivingYards << endl;
			cout<<"* <7>Rushing Yards:      :"<<team[index].numRushYards << endl;
			cout<<"* <8>Return              :"<<endl;
			cout<<"**************************"<<endl;
			cout<<endl <<"Choice: ";
			cin >> choice;
			switch(choice){
				case '1':
					cout<<"Enter Player Name: ";
					cin >> team[index].name;
                    break;
                case '2':
					cout<<"Enter Player Position: ";
					cin >> team[index].position;
                    break;
                case '3':
					cout<<"Enter Number of TouchDowns: ";
					cin >> team[index].numOfTD;
                    break;
				 case '4':
					cout<<"Enter Number of Catches: ";
					cin >> team[index].numOfCatches;
                    break;
                case '5':
					cout<<"Enter Passing Yards: ";
					cin >> team[index].numPassYards;
                    break;
				case '6':
					cout<<"Enter Receiving Yards: ";
					cin >> team[index].numReceivingYards;
                    break;
                case '7':
					cout<<"Enter Rushing Yards: ";
					cin >> team[index].numRushYards;
                    break;
				case '8':
					cout<< "Returning to Main Menu..." << endl;
					system("pause");
					break;
                default:
                    cout << "Enter Valid Input (1-4)";
			}
		}
	}
	else cout << "Player Not Found!" << endl;
}

void writeFile(playerType (&team)[TEAM_SIZE]){
	ofstream fout;
	fout.open("output.txt");
	for (int i = 0; i < TEAM_SIZE; i++) {
		fout << team[i].name << endl;
        fout << team[i].position<< endl;
        fout << team[i].numOfTD<< endl;
        fout << team[i].numOfCatches<< endl;
        fout << team[i].numPassYards<< endl;
        fout << team[i].numReceivingYards<< endl;
        fout << team[i].numRushYards<< endl;
	}
	fout.close();
}
