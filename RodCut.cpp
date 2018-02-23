// CSE 101 Winter 2018, PA 3
//
// Name: Vincent Cannalla
// PID: A13006747
// Sources of Help: TODO
// Due: February 23rd, 2018 at 11:59 PM

/* to run:
make TestRodCut
build/TestRodCut testcases/rod-22.txt
*/

#ifndef __RODCUT_CPP__
#define __RODCUT_CPP__

#include "RodCut.hpp"
#include "TwoD_Array.hpp"
#include <iostream>
#include <algorithm>

int cols;
TwoD_Array<int> * arr;
std::map<int, int> * price_map;

//first length will always be 1
void firstLengthSet(){
	for(int i = 0; i <= cols; i++){
		if(1 <= i) 
			arr->at(1, i) = i;
	}
}

void set(std::map<int, int> * prices, int length){
	price_map = prices;
	cols = length + 1;
	arr = new TwoD_Array<int>(std::max_element(price_map->begin(), price_map->end(),
    [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.second < p2.second; })->second, cols);
	firstLengthSet();
}

int findMax(){
	int max = 0;
	int value;
	//go through price map
	for(auto price_it = next(price_map->begin(),1); price_it != price_map->end(); price_it++){
		//for each amount of cuts, determine how much money can be made
		int cut_amounts = price_it->first;
		for(int curr = 0; curr < cols; curr++){
			if(cut_amounts > curr){
				value = arr->at((prev(price_it,1))->first, curr);
				max = (value > max)? max = value : max;
				arr->at(cut_amounts, curr) = value;
			}
			if(cut_amounts < curr){
				int use = (curr / cut_amounts) * price_it->second;
				use += ((curr%cut_amounts) != 0)? arr->at((prev(price_it,1))->first,
				 (curr%cut_amounts)): 0;
				value = MAX(arr->at((prev(price_it,1))->first, curr), use);
				max = (value > max)? max = value : max;
				arr->at(cut_amounts, curr) = value;

			}
			if(cut_amounts == curr){
				value = MAX(arr->at((prev(price_it,1))->first, curr), price_it->second);
				max = (value > max)? max = value : max;
				arr->at(cut_amounts, curr) = value;
			}
		}	
	}

	return max;
}

int rodcut(std::map<int, int> prices, int length) {
	set(&prices, length);

	return findMax();
}
#endif
