// CSE 101 Winter 2016, PA 3
//
// Name: TODO put both partners' info if applicable
// PID: TODO
// Sources of Help: TODO
// Due: February 23rd, 2018 at 11:59 PM

#ifndef __GRID_SUM_CPP__
#define __GRID_SUM_CPP__

#include "TwoD_Array.hpp"
#include "GridSum.hpp"

TwoD_Array<int>* graph = NULL;

// Perform the precomputation step here
GridSum::GridSum (TwoD_Array<int>& grid) {
	for(int rows = 0; rows < grid.getNumRows(); rows++){
		for(int cols = 0; cols < grid.getNumCols(); cols++ ){
			if(cols != 0){
				grid.at(rows, cols) = grid.at(rows, cols) + grid.at(rows, cols-1);
			}
		}
	}

	for(int cols = 0; cols < grid.getNumCols(); cols++ ){
		for(int rows = 0; rows < grid.getNumRows(); rows++){
			if(rows != 0){
				grid.at(rows, cols) = grid.at(rows, cols) + grid.at(rows-1, cols);
			}
		}
	}
	graph = &grid;
}

// Perform the query step here
int GridSum::query (int x1, int y1, int x2, int y2) {
	graph->printOut();
	std::cout<<graph->at(x1,y1) << "\n";
	std::cout<<graph->at(x2,y2) << "\n";

	int first = 0;
	if(x1 != 0){
		first = graph->at(x1-1,y2);
	}
	std::cout<<first << "\n";
	int second = 0;
	if(y1 != 0){
		second = graph->at(x2,y1-1);
	}
std::cout<<second << "\n";
	int third = 0;
	if(y1 != 0 && x1 != 0){
		third = graph->at(x1-1,y1-1);
	}
std::cout<<third << "\n";
	return graph->at(x2,y2) - first - second + third;
  return 0;
}

#endif
