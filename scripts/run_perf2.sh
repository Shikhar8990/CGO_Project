#! /bin/bash

rm -f output.txt $1.txt file.nocomma
rm -f output.txt $2.txt file.nocomma2
rm -f output.txt $3.txt file.nocomma3

counter=1
while [ $counter -le 5 ] 
do
  echo "Running iteration $counter"
  perf stat -e $1:u,$2:u -r5 python test_model.py examples/images/cat_gray.jpg &>> output.txt
  let "counter=counter+1"
done
awk '/branch-misses/' output.txt >> $1.txt
#awk '/cache-misses/' output.txt >> $1.txt
#awk '/L1-dcache-load-misses/' output.txt >> $1.txt
#awk '/cycles/' output.txt >> $1.txt
#awk '/r2a1/' output.txt >> $1.txt #port1
#awk '/r40a1/' output.txt >> $1.txt #port6

sed 's/,//g' $1.txt > file.nocomma
table_name="$1tables"
awk '{print $1}' file.nocomma > $table_name
#libreoffice --calc $table_name &

awk '/branches/' output.txt >> $2.txt
#awk '/cache-references/' output.txt >> $2.txt
#awk '/L1-dcache-loads/' output.txt >> $2.txt
#awk '/r412e/' output.txt >> $2.txt #LLC misses
#awk '/r8a1/' output.txt >> $2.txt #Port3

sed 's/,//g' $2.txt > file.nocomma2
table_name="$2tables"
awk '{print $1}' file.nocomma2 > $table_name
#libreoffice --calc $table_name &

#awk '/instructions/' output.txt >> $3.txt
#awk '/L1-dcache-stores/' output.txt >> $3.txt
##awk '/L1-dcache-load-misses/' output.txt >> $3.txt
#awk '/r4f2e/' output.txt >> $3.txt #LLC refs
#awk '/r4a1/' output.txt >> $3.txt #Port2
#awk '/r10e/' output.txt >> $3.txt #any uops

##sed 's/,//g' $3.txt > file.nocomma3
##table_name="$3tables"
##awk '{print $1}' file.nocomma3 > $table_name
#libreoffice --calc $table_name

echo " I am done"

