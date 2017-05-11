#-------------------------- Inner Peace------------------------------#
#`chmod 777 stats_lenet_16kb`;
#$file_in[0] = "stats_lenet_32kbL1_256kbL2_2MbL3_assoc_2.txt";
#$file_in[1] = "stats_lenet_32kbL1_256kbL2_2MbL3_assoc_4.txt";
#$file_in[2] = "stats_lenet_out.txt";
#$file_in[3] = "stats_lenet_32kbL1_256kbL2_2MbL3_assoc_16.txt";

$file_in[0] = "stats_siamese_32kbL1_256kbL2_2MbL3_assoc_1.txt";
$file_in[1] = "stats_siamese_32kbL1_256kbL2_2MbL3_assoc_2.txt";
$file_in[2] = "stats_siamese_32kbL1_256kbL2_2MbL3_assoc_4.txt";
$file_in[3] = "stats_siamese_32kbL1_256kbL2_2MbL3_assoc_8.txt";
$file_in[4] = "stats_siamese_32kbL1_256kbL2_2MbL3_assoc_16.txt";

#$file_in = "stats_lenet_out.txt";
$instance_out = "stats_siamese_assoc_cmp.csv";
#$instance_out = "stats_lenet_32kbL1_256kbL2_2MbL3_assoc_16.csv";
open(FILE_OUT,">$instance_out") || die "Please provide a valid file output or check for permission for creating file in this folder";

print FILE_OUT "metric,assoc_2,assoc_4,assoc_8,assoc_16\n";
for($x=0;$x<5;$x++)
{
	open(FILE_IN,"$file_in[$x]") || die "Please provide a valid file output or check for permission for creating file in this folder";
	@total = <FILE_IN>;
	close(FILE_IN);
	$i=0;
	$m=0;
	foreach $line(@total)
	{
	  chomp($line);
	  $line =~s/ {1,}/ /g;
	  @x=split(" ",$line);
	  $value[$x][$m] = $x[1];
	  @y=split(/\./,$x[0]);
	  $key[$m] = $y[1];
	  $m++;
	  #print FILE_OUT $y[1].",".$x[1]."\n";
	  if($line =~ "cache_write_miss" |
	     $line =~ "cache_write_access" |
	     $line =~ "cache_read_access" |
	     $line =~ "cache_total_access" |
	     $line =~ "cache_read_miss" |
	     $line =~ "cache_mshr_unavailable")
	  {
	      if($i==0)
	      {
	        $cache_read_miss = $x[1];
	        $i++;
	      }					
	      elsif($i==1)
              {
                $cache_write_miss = $x[1];
                $i++;
              }					
	      elsif($i==2)
	      {
	        $cache_read_access = $x[1];
	        $i++;
	      }					

	      elsif($i==3)
	      {
	        $cache_write_access = $x[1];
	        $i++;
	      }					

              elsif($i==4)
	      {
	        $cache_total_access = $x[1];
	        $i++;
	      }
	      elsif($i==5)
	      {
	        $mshr = $x[1];
	        $i = 0;
		$read_hit  = $cache_read_access - $cache_read_miss;
		$write_hit = $cache_write_access - $cache_write_miss;
	        $actual_access = $cache_total_access - $mshr;
	        print "write access is ".$cache_write_access." Write hit is ".$cache_write_miss."\n";
		$hit_ratio = ($write_hit + $read_hit) / $actual_access;
	        $hit_ratio *=100;
		$key[$m] = "hit_ratio";
		$value[$x][$m] = $hit_ratio;
		$m++;
	        print "hit_ratio,".$hit_ratio."\n";
	      }
	  }
	}
}
for($k=0;$k<$m;$k++)
{
	print FILE_OUT $key[$k].",";
	for($mm =0;$mm<4;$mm++)
	{
		print FILE_OUT $value[$mm][$k].",";
	}
	print FILE_OUT "\n";
}

close(FILE_OUT);
  
