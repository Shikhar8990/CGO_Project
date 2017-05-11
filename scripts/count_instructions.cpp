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
#include <boost/iostreams/filtering_streambuf.hpp>  
#include <boost/iostreams/filtering_stream.hpp>     
#include <boost/iostreams/filter/gzip.hpp>          

using namespace std;
//ofstream OutFile;
FILE * trace;
map<long int, long int> delta_map;

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[]) {
  ifstream inFile(argv[1]);
  string line;
  uint64_t line_cntr=0;
  uint64_t instr_count=0;
    uint64_t bubble=0;                            

  ifstream file(argv[1], ios_base::in | ios_base::binary);
  boost::iostreams::filtering_istream in;                                            
  in.push(boost::iostreams::gzip_decompressor());                                    
  in.push(file);                                                                   
	
  for(std::string str; std::getline(in, str);) {
    string str_addr;                            
    uint64_t addr;                              
    int rw;                                     
    string op;                                  
    istringstream iss(str);                     
    iss>>bubble>>str_addr>>rw;                  
    
    line_cntr++;
    instr_count = instr_count + bubble;
  }
  cout<<" Instructions count "<<instr_count<<endl;
  cout<<" Line Count "<<line_cntr<<"   "<<bubble<<endl;  
}

