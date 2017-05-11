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
#include <zlib.h>
#include <stdint.h>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;
//ofstream OutFile;
FILE * trace;
/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[]) {
  ifstream inFile(argv[1]);
  string line;
  long int line_cntr=0;
  long int prev_addr=0;

  ifstream file(argv[1], ios_base::in | ios_base::binary);
  boost::iostreams::filtering_istream in;
  in.push(boost::iostreams::gzip_decompressor());
  in.push(file);

  int bubble = 3;
  uint64_t counter=0;

  gzFile fi0 = gzopen("cifar_ramulator_cpu.gz","wb");

  for(std::string str; std::getline(in, str);) {
    string str_addr;
    uint64_t addr;
    string rw;
    string op;
    long int pc;
    int cntr;
    istringstream iss(str);
    char *pch;
    pch = strtok(&str[0]," \n");
    cntr=0;
    while(pch != NULL) {
      if(cntr == 0) {
        rw = pch;
      }
      //if(cntr == 2)
        //bubble = stol(pch, NULL);
      else if(cntr == 1) {
        str_addr = pch;
	str_addr.erase(0,2);
      }
      pch = strtok(NULL," \n");
      cntr++;
    }

    addr = strtoul(&str_addr[0], NULL, 16);

    gzprintf(fi0, &((to_string(bubble))[0]));
    gzprintf(fi0, " ");
    gzprintf(fi0, &((to_string(addr))[0]));
    gzprintf(fi0, " ");
    gzprintf(fi0, &rw[0]);
    gzprintf(fi0, "\n");
    //break;
    counter++;
    if(counter>2689381744)
      break;
  }
  gzclose(fi0);
} 
