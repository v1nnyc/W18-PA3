// CSE 101 Winter 2018, PA 3
//
// DO NOT MODIFY

#ifndef __USB_HPP__
#define __USB_HPP__

#include <vector>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int find_files_naive(int USBsize, std::vector<int>& files);

int find_files_memoized(int USBsize, std::vector<int>& files);

int find_files_dp(int USBsize, std::vector<int>& files);

#endif
