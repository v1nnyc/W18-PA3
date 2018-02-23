// CSE 101 Winter 2018, PA 3
//
// Name: Vincent Cannalla
// PID: A13006747
// Sources of Help: TODO
// Due: February 23rd, 2018 at 11:59 PM

/* to run:
make TestUSB
build/TestUSB testcases/input_file INDEX
Where  INDEX  is  1 ,  2 , or  3  corresponding with naive, memoized, or
DP respectively.
*/

#ifndef __USB_CPP__
#define __USB_CPP__

#include <map>
#include "USB.hpp"
#include "TwoD_Array.hpp"

int count = 0; 
int find_files_naive(int USBsize, std::vector<int>& files) {
  int min = -1;
  for (auto it = files.begin(); it != files.end(); ++it) {
    if (USBsize == *it) {   // 1 is the minimum number of possible files
      return 1;
    }
    else if (USBsize > *it) {
      // assume per the problem statement that the USB size is always met
      int files_used = find_files_naive(USBsize - *it, files) + 1;
      if (min == -1 || files_used < min) {
        min = files_used;
      }
    }
    // do nothing if file size is larger than the USB size
  }
  return min;

}

std::map<int, int> memoize;
int find_files_memoized(int USBsize, std::vector<int>& files) {
  memoize.insert(std::pair<int,int>(1,1));
  int min = -1;

  //if the filesize we're looking for is already in the map
  auto first_check = memoize.find(USBsize);
  if(first_check != memoize.end()){
    return first_check->second;
  }

  //otherwise go through them like the other solution
  for (auto it = files.begin(); it != files.end(); ++it) {
    //base case
    if (USBsize == *it) { 
      return 1;
    }
    if (USBsize > *it) {
      int files_used = find_files_memoized(USBsize - *it, files) + 1;
      if (min == -1 || files_used < min) {
        auto new_size = memoize.find(USBsize);
        //if the new filesize is not already in the map
        if(new_size == memoize.end()){
          memoize.insert(std::pair<int,int>(USBsize,files_used));
        }
        //if the filesize is already in the map, and this is a smaller # of files
        if(new_size != memoize.end() && new_size->second > files_used){
          new_size->second = files_used;
        }
        min = files_used;
      }
    }
  }

  return min;
}

int value;
TwoD_Array<int> * arr;
std::vector<int>* filesPoint;

void set(std::vector<int>& files, int USBsize){
  filesPoint = &files;
  arr = new TwoD_Array<int>(*std::max_element(files.begin(),files.end())+1, USBsize+1);
  for(int i = 0; i <= USBsize; i++){
    if(1 <= i) 
      arr->at(1, i) = i;
  }
  std::sort (files.begin(), files.end()); 
}

int find_files_dp(int USBsize, std::vector<int>& files) {
  //TwoD_Array<int> * 
  
  set(files, USBsize);

  //go through price map
  for(auto file_sizeit = next(files.begin(),1); file_sizeit != files.end(); file_sizeit++){
    //for each amount of cuts, determine how much money can be made
    int file_size = *file_sizeit;
    for(int curr = 0; curr < USBsize + 1; curr++){
      if(file_size > curr){
        value = arr->at(*(prev(file_sizeit,1)), curr);
        arr->at(file_size, curr) = value;
      }
      if(file_size < curr){
        int use = (curr / file_size);
        use += ((curr%file_size) != 0)? arr->at(*(prev(file_sizeit,1)),
         (curr%file_size)): 0;
        value = MIN(arr->at(*(prev(file_sizeit,1)), curr), use);
        arr->at(file_size, curr) = value;

      }
      if(file_size == curr){
        value = MIN(arr->at(*(prev(file_sizeit,1)), curr), curr/ *file_sizeit);
        arr->at(file_size, curr) = value;
      }
    } 
  }
  
  return arr->at(*std::max_element(files.begin(),files.end()), USBsize);
}
#endif
