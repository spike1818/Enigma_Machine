//============================================================================
// Name        : Enigma.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

int getSize(string s){
	int count = 0;
	while(s[count] != NULL){
		count++;
	}
	return count;
}

string capitalize(string s){
	string cap = "";
	for (int i = 0; i < getSize(s); i++){
		if ((int)s[i] > 90){
			s[i] = (int)s[i] - 32;
		}
	}
	return s;
}

string rotate(string s){
	char first = s[0];
	string temp = s.substr(1);
	return temp + first;
}

int index(string s, char c){
	int pos = 0;

	while(s[pos] != c){
		pos++;
	}

	return pos;
}


string encrypt(string s){
	string output = "";
	s = capitalize(s);
	char next;
	int pos;
	string r1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string r2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string r3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	string c1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
	string c2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
	string c3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

	string standard = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string reflector = "EJMZALYXVBWFCRQUONTSPIKHGD";

	for (int i = 0; i < getSize(s); i++){
		next = s[i];
		if ((int)s[i] != 32){
			//do encryption stuff

			pos = index(standard, next);

			// Rotor 1
			next = r1[pos];
			pos = index(c1,next);

			//Rotor 2
			next = r2[pos];
			pos = index(c2,next);

			//Rotor 3
			next = r3[pos];
			pos = index(c3,next);

			//Reflector
			next = standard[pos];
			pos = index(reflector, next);

			//Rotor 3 again
			next = c3[pos];
			pos = index(r3, next);

			//Rotor 2 again
			next = c2[pos];
			pos = index(r2, next);

			//Rotor 1 again
			next = c1[pos];
			pos = index(r1, next);

			next = standard[pos];


			// rotor stuff
			r1 = rotate(r1);
			c1 = rotate(c1);
			if ((i+1) % 26 == 0){
				r2 = rotate(r2);
				c2 = rotate(c2);
			}
			if ((i+1) % 647 == 0){
				r3 = rotate(r3);
				c3 = rotate(c3);
			}
		}
		output = output + next;
	}

	return output;
}


int main() {

	string message = "Hello World";
	string encryption = encrypt(message);
	cout << encryption << endl;
	cout << encrypt(encryption) << endl;
	return 0;
}
