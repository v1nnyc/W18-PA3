// CSE 101 Winter 2018, PA 3
//
// Name: TODO put both partners' info if applicable
// PID: TODO
// Sources of Help: TODO
// Due: February 23rd, 2018 at 11:59 PM

#ifndef __RODCUT_CPP__
#define __RODCUT_CPP__

#include "RodCut.hpp"
#include "TwoD_Array.hpp"
#include <iostream>

int rodcut(std::map<int, int> prices, int length) {
	int rows = prices.size() + 1;
	int cols =  length + 1;
	int max = 0;


	//finding max in list
	auto x = std::max_element(prices.begin(), prices.end(),
    [](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.second < p2.second; });


	TwoD_Array<int> * arr = new TwoD_Array<int>(x->first, cols);

	//first length will always be 1
	for(int i = 0; i <= cols; i++){
		int value =0;
		if(1 <= i){
			arr->at(1, i) = i;
		}
	}

	int value; 
	for(auto it = next(prices.begin(),1); it != prices.end(); it++){
		for(int j = 0; j < cols; j++){
			if(it->first > j){
				value = arr->at((prev(it,1))->first, j);
				if(value > max) max = value;
				arr->at(it->first, j) = value;
			}
			if(it->first == j){
				value = MAX(arr->at((prev(it,1))->first, j), it->second);
				if(value > max) max = value;
				arr->at(it->first, j) = value;
			}
			if(it->first < j){
				int use = (j / it->first) * it->second;
				if((j%it->first) != 0){
					use +=arr->at((prev(it,1))->first, (j%it->first));
				}
				value = MAX(arr->at((prev(it,1))->first, j), use);
				if(value > max) max = value;
				arr->at(it->first, j) = value;

			}
		}	
	}

	/*
	for(int i = 1; i <= arr->getNumRows(); i++){
		for(int j = 0; j < arr->getNumCols(); j++){
			std::cout<< arr->at(i, j) << "  ";
		}
		std::cout<<"\n";
	}
	*/
	

  return max;
}
#endif
