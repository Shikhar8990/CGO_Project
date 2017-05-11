import sys
from sys import argv
script, filename, stat = sys.argv

fout = open(filename, 'r')
for line in fout:
  list_word = line.split()
  #print line+str(len(line.split()))
  if(len(line.split()) > 2):
    if(list_word[2] == argv[2]):
      print list_word[0]+' '+list_word[1]+' '+list_word[2]
