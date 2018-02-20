// CSE 101 Winter 2018, PA 3
//
// Name: Vincent Cannalla
// PID: A13006747
// Sources of Help: lecture slides
// Due: February 23rd, 2018 at 11:59 PM

#ifndef __LCS_CPP__
#define __LCS_CPP__

#include "LCS.hpp"
#include "iostream"

TwoD_Array<int> * arr;
std::string string1;
std::string string2;

//sets global variables for other methods to use
void set(std::string s1, std::string s2){
	string1 = s1;
	string2 = s2;
	arr = new TwoD_Array<int>(string1.length()+1, string2.length()+1);
}

//sets the array with indexes of common chars
void setArray(){
	for(int rows = 0; rows <= string1.length(); rows++){
		for(int cols = 0; cols <= string2.length(); cols++){
			//need padding of 0's bc using TwoD_Array
			if(rows == 0 || cols == 0) 
				arr->at(rows,cols) = 0;
			//use rows-1 and cols-1 bc we're one ahead bc padding
			else if(string1[rows-1] == string2[cols-1])
				arr->at(rows,cols) = arr->at(rows-1,cols-1) + 1;
			//if not equal use max
			else 
				arr->at(rows,cols) = MAX(arr->at(rows-1,cols), arr->at(rows,cols-1));
		}
	}
}

std::string findLCS(){
	//creating char array to return
	int index = arr->at(string1.length(), string2.length());
	char str[index+1];
	str[index] = '\0';

	//variables to loop through strings
	int first = string1.length();
	int second = string2.length();

	while(first > 0 && second > 0){
		if(string1[first-1] == string2[second-1]){
			str[index-1] = string1[first-1];
			first--; second--; index--;
		}
		else if(arr->at(first-1,second) > arr->at(first,second-1)) 
			first--;
		else 
			second--;

	}

	return str;
}



std::string lcs(std::string s1, std::string s2) {
	set(s1,s2);
	setArray();

	return findLCS();
}
#endif
