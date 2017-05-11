#include <iostream>
#include <fstream>
#include <deque>
#include "map"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <bitset>
#include <climits>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;
//ofstream OutFile;
FILE * trace;
map<long int, bitset<64>> unique_map; //pfn, unique_CCs
map<long int, long int> refs_per_page; //pfn, number of accesses
long int cnt_arr[65];
long int pages=0;
long int pages1=0;
// The running count of instructions is kept here
// make it static to help the compiler optimize docount

void processMap(long int addr) {
  long int page_num = 0;
  long int cc = 0;
  page_num = addr>>12;
  cc = (addr>>6)&0x3f;
  auto mapit = unique_map.find(page_num);
  if(mapit == unique_map.end()) {
    bitset<64> newbit_vector;
    newbit_vector[cc] = 1;
    unique_map[page_num] = newbit_vector;
    //unique_map[page_num] = 1;
    pages1++; 
  } else {
    (mapit->second)[cc] = 1;
  } 
}

void processMap1(long int addr) {
  long int page_num = addr>>12;
  auto fit = refs_per_page.find(page_num);
  if(fit == refs_per_page.end()) {
    refs_per_page[page_num] = 1;
  } else {
    fit->second = (fit->second) + 1;
  }
}
/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[]) {

  ifstream file(argv[1], ios_base::in | ios_base::binary);
  boost::iostreams::filtering_istream in;
  in.push(boost::iostreams::gzip_decompressor());
  in.push(file);

  string line;
  long int prev_addr=0;
  for(string str; getline(in, str);) {
    istringstream iss(str);
    long int cyc;
    char rw;
    string hexaddr;
    long int addr;
    if(!(iss>>rw>>hexaddr)) { break; }
    else {
      addr=0;
      hexaddr.erase(0,2);
      addr = std::stoul(hexaddr, NULL, 16);
      processMap(addr);
      processMap1(addr);
    }
  }
  for(int x=0; x<65; x++) 
    cnt_arr[x]=0;

  //iterate the unique map to find the unique CCs for that page
  //find the memory refs for the page 
  //increment the array which maps the unique CCs to references 
  for(auto it = unique_map.begin(); it != unique_map.end(); it++) {
    bitset<64> bitvec = it->second;
    int uniq = bitvec.count();
    long int refs = refs_per_page[it->first];
    cnt_arr[uniq] = cnt_arr[uniq] + refs; 
  }
  for(int x=0; x<65; x++) 
    cout<<x<<","<<cnt_arr[x]<<endl;
  cout<<" Unique Pages= "<<pages<<endl;
  cout<<" Unique Pages= "<<pages1<<endl;
}
