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


using namespace std;
//ofstream OutFile;
FILE * trace;
map<long int, bitset<128>> unique_map;
map<long int, int> unique_map2;
long int cnt_arr[129];
long int pages=0;
long int pages1=0;
// The running count of instructions is kept here
// make it static to help the compiler optimize docount

void processMap(long int addr) {
  long int page_num = 0;
  long int cc = 0;
  page_num = addr>>13;
  cc = (addr>>6)&0x7f;
  auto mapit = unique_map.find(page_num);
  if(mapit == unique_map.end()) {
    bitset<128> newbit_vector;
    newbit_vector[cc] = 1;
    unique_map[page_num] = newbit_vector;
    //unique_map[page_num] = 1;
    pages1++; 
  } else {
    //bitset<128> bitvec;
    //bitvec = mapit->second();
    //bitvec[cc] = 1;
    //unique_map[page_num] = bitvec;
    //mapit->second() = bitvec; 
    (mapit->second)[cc] = 1;
    //auto t4 = mapit->second;
    //*t4[cc] = 1;   
  } 
}

void processMap1(long int addr) {
  long int addr1 = 0;
  addr1 = addr>>13;
  auto mapit = unique_map2.find(addr1);
  if(mapit == unique_map2.end()) {    
    unique_map2[addr1] = 1;            
    pages++;                         
  }                                  
}
/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[]) {
  ifstream inFile(argv[1]);
  string line;
  int a,b,c;
  long int prev_addr=0;
  long int numn = 0;
  string rw = "W";
  string pc = "0fc18da80";
  while(getline(inFile, line)) {
    uint64_t addr;
    istringstream iss(line);
    char *pch;
    //cout<<"Line "<<line<<endl;
    //if(line.size() < 2) break;
    pch = strtok(&line[0]," ");
    //if((!(iss>>a>>b>>c)) && (!(iss>>a>>b))) { break; }
    while(pch != NULL) {
      if((strcmp(&rw[0],pch)==0) || (strcmp(&pc[0], pch)==0)) {
	//cout<<"Here"<<endl;
	//continue;
      }
      else {
        //cout<<pch<<endl;
	addr = std::stoul(pch, NULL, 16);
	//cout<<addr<<endl;
	processMap(addr);
      }
      pch = strtok(NULL," ");
    }
    numn++;
  }

  for(int x=0; x<129; x++) 
    cnt_arr[x]=0;

  for(auto it = unique_map.begin(); it != unique_map.end(); it++) {
    bitset<128> bitvec = it->second;
    int  cnt = bitvec.count();
    cnt_arr[cnt] = cnt_arr[cnt]+1;
  }
  for(int x=0; x<129; x++) 
    cout<<x<<","<<cnt_arr[x]<<endl;
  cout<<" Unique Pages= "<<pages<<endl;
  cout<<" Unique Pages= "<<pages1<<endl;
  cout<<" Lines= "<<numn<<endl;
}
