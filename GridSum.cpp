// CSE 101 Winter 2016, PA 3
//
// Name: TODO put both partners' info if applicable
// PID: TODO
// Sources of Help: TODO
// Due: February 23rd, 2018 at 11:59 PM

/* to run:
make TestGridSum
build/TestGridSum testcases/gridSum1.txt 
*/

#ifndef __GRID_SUM_CPP__
#define __GRID_SUM_CPP__

#include "TwoD_Array.hpp"
#include "GridSum.hpp"

TwoD_Array<int>* graph;

void set(TwoD_Array<int>& grid){
	graph = &grid;
}

void setArray(bool rows){
	auto out = (rows)? graph->getNumRows(): graph->getNumCols();
	auto in = (!rows)? graph->getNumCols(): graph->getNumRows();
	for(int outer = 0; outer < out; outer++){
		for(int inner = 0; inner < in; inner++ ){
			if(inner != 0){
				graph->at(outer, inner) = graph->at(outer, inner) + 
				((rows)? graph->at(outer, inner-1): graph->at(outer-1, inner));
			}
		}
	}
}

GridSum::GridSum (TwoD_Array<int>& grid) {
	set(grid);
	setArray(true);
	setArray(false);
}

int addSum(int x1, int y1, int x2, int y2){
	int first = graph->at(x2,y2);
	int second = (x1 != 0) ? graph->at(x1-1,y2) : 0;
	int third = (y1 != 0)? graph->at(x2,y1-1) : 0;
	int fourth = (y1 != 0 && x1 != 0)? graph->at(x1-1,y1-1) : 0;

	return first - second - third + fourth;
}

int GridSum::query (int x1, int y1, int x2, int y2) {
	graph->printOut();

	return addSum(x1, y1, x2, y2);
}

#endif
