#include <iostream>

// windows specific fns
//#include "windows.h"

// basic file operations
#include <fstream>

#include <string>
#include <cmath>
#include <iomanip>
#include <bitset>

using namespace std;

struct ir{
	string binary;
	string mneumonic;
	string operand;
	int instr;
	int op;
	
};

ir fetch(string ram){
	ir temp;
	int value = 0;
	int indexCounter = 0;
	std::string::size_type sz;   // alias of size_t
	
	temp.mneumonic = ram.substr(0,4);
	temp.binary = temp.mneumonic;
	temp.operand = ram.substr(4,8);
	
	//cout << "inside fetch " << temp.mneumonic << endl;
	
	if (temp.mneumonic == "0000") {
		temp.mneumonic = "LDA";
	}
	else 
		if (temp.mneumonic == "0001") {
			temp.mneumonic = "ADD";
		}
		else 
			if (temp.mneumonic == "0010") {
				temp.mneumonic = "SUB";
			}
			else 
				if (temp.mneumonic == "1110") {
					temp.mneumonic = "OUT";
				}
				else 
					if (temp.mneumonic == "1111") {
						temp.mneumonic = "HLT";
					}
					else{ 
						cout << "***OPERAND SYNTAX ERROR ****" << endl;
						system("exit");
						
					} 
			
	for(int i = temp.binary.length()-1; i >= 0; i--) {
 
		if(temp.binary [i] == '1') {
			value += pow(2, indexCounter);
		}
		indexCounter++;
	}
	temp.instr = value;
	value = 0;
	indexCounter = 0;
	
	
	if (temp.instr != 14 && temp.instr != 15){
	
		for(int i = temp.operand.length()-1; i >= 0; i--) {
	 
			if(temp.operand [i] == '1') {
				value += pow(2, indexCounter);
			}
			indexCounter++;
		}
		
		
		//temp.op = std::stoi (temp.operand,&sz);
		temp.op = value;
		temp.operand = "R" + to_string(value);
	}
	else
		temp.operand = "";

	
	return temp;
}

bool readFile(int argc, char *argv[], string ram[]){
	bool result = true;
	int i = 0;
	//char ch;
	if (argc > 1) {
        cout << "argv[1] = " << argv[1] << endl; 
		
		ifstream infile(argv[1]); //open the file
		
		if (infile.is_open() && infile.good()) {
			//cout << "File is now open!\nContains:\n";
        
			
			getline(infile, ram[i]);
			
			while (i < 16 && infile)
			{
				//cout << ram[i] << endl;
				i++;
				getline(infile,ram[i]);
				
			}
			//cout << endl;
			//cout << "Closing file" << endl;
			infile.close();
        
		}
		else {
			cout << "Failed to open file..";
			result = false;
		}
		
    } else {
        cout << "No file name entered. Exiting...";
        result = false;
    }

	return result;
}

int getData(int operand, string ram[]){
	int index = 0;
	int value = 0;
	int indexCounter = 0;
	
	//for (int i = 0; i <= 15; i++){
		//cout << ram[i] << endl;
	//}
	string temp = ram[operand];
	//cout << "OPerand = " << operand << " " << "temp = " << temp <<  endl;
	//system("pause");


	for(int i = temp.length()-1; i >= 0; i--) {
 
		if(temp[i] == '1') {
			value += pow(2, indexCounter);
		}
		indexCounter++;
	}
	//cout << "getData returning " << value;
	return value;
}


void printSAP1(string ram[], int &pc, int a, int b, bool p){
	system("cls");
	cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
	cout << "-" << setw(27) << right << "SAP-1" << right << setw(17) << "-" << endl;
	
	cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
	cout << "-   RAM" << setw(20) << "PC: " << setw(4) << bitset<4>(pc) << right << setw(14) << "-" << endl;
	for (int i = 0; i < 16; i++){

		if (i == 3)
			cout  << "- R" << setw(2) << left <<i << setw(10) << right << ram[i] << setw(15) << right << "A REGISTER: " << bitset<8>(a)<< setw(7) << right << "-" << endl; 
		else 
			if (i == 10)
				cout  << "- R" << setw(2) << left <<i << setw(10) << right << ram[i] << setw(15) << right << "B REGISTER: " << bitset<8>(b)<< setw(7) << right << "-" << endl; 
			else
				if (i == 13){
					if (p)
						cout  << "- R" << setw(2) << left <<i << setw(10) << right << ram[i] << setw(20) << right << "OUTPUT REGISTER: " << setw(8) << left << a <<  " -" << endl; 
					else
						cout  << "- R" << setw(2) << left <<i << setw(10) << right << ram[i] << setw(20) << right << "OUTPUT REGISTER: " << setw(10) << right << "-" << endl;
				}
				else
					cout  << "- R" << setw(2) << left <<i << setw(10) << right << ram[i] << setw(30) << right << "-" << endl; 
		
	}
	cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;
	cout << "- INSTRUCTION REGISTER: " << ram[pc].substr(0,4) << "  " << ram[pc].substr(4,8) << setw(11) << right <<  "-" << endl;
	cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl << endl;
	cout << "PRESS <ENTER> to step through your program" << endl;
	system("pause");
	
}

int main(int argc, char *argv[]){
	int aRegister = 0;
	int bRegister = 0;
	int pc = 0;
	string memory[16] = {""};
	ir iRegister;
	bool p = false;
	

	
	system ("cls");
	
	if(readFile(argc, argv, memory)) {
	//printSAP1(memory,pc, aRegister, bRegister, memory[iRegister.op]);
	//printSAP1(memory,pc, aRegister, bRegister,p);
	
		do {
			printSAP1(memory,pc, aRegister, bRegister, p);
			p = false;
			iRegister = fetch(memory[pc]);
			switch(iRegister.instr){
				case 0:
					//cout << "doing lda: ram = " << memory[0] << endl;
					aRegister = getData(iRegister.op, memory) ;
					//cout << "A Register = " << aRegister << endl;
					break;
				case 1:
					bRegister = getData(iRegister.op, memory) ;
					//cout << "B Register = " << bRegister << endl;
					aRegister = aRegister + bRegister;
					//cout << "A Register = " << aRegister << endl;
					break;
				case 2:
					bRegister = getData(iRegister.op, memory) ;
					//cout << "B Register = " << bRegister << endl;
					aRegister = aRegister - bRegister;
					//cout << "A Register = " << aRegister << endl;
					break;				
				case 14:
					//cout << "OUT = " << aRegister << endl;
					p = true;
					break;
				case 15:
					break;
				
			}
			pc++;		
			

			
		} while (pc <= 15 && iRegister.instr != 15);
	}
	else return -1;

	return 0;
}
