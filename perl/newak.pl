# released under the GPL on 2004-07-21 - written by lithron@gmail.com
# http://www.lithron.com
# "newak.pl" version 0.04

use strict;
use warnings;
use Algorithm::Bucketizer;
use File::Copy;

my $mediasize = 1024 * 1024 * 1024 * 4.3; # use 4.3 if you want DVD
my $maxtime = 10; # max amount of seconds spent optimizing the files
my $maxrounds = 10000; # max amount of tries to optimize 

my %h; # temp hash used for tracking file names and sizes

# grab every file in the directory (*) and check its name and size..
foreach my $x (glob "*") {
  # skip to next unless file exists and has size
  # AND the file is a 'plain' file.  ie, Not a tty, or a socket
  next unless ((-s $x) and (-f $x));
  # get the size of the file
  my $tempsize = (stat($x))[7];
  # skip if file is larger than $mediasize
  $h{$x} = $tempsize unless ($tempsize > $mediasize);
  # free our variable, because sometimes I like being extra safe 
  undef $tempsize;
}

my $b = Algorithm::Bucketizer->new(bucketsize=>$mediasize, algorithm=>'retry');

# iterate over each key, and add it to the newly created
# Algorithm::Bucketizer bucket, $b.
foreach my $key (keys %h) {
  $b->add_item($key, $h{$key});
}

# try and optimize the file layouts in the buckets
$b->optimize(algorithm=>'random', maxrounds=>$maxrounds, maxtime=>$maxtime);

# for each bucket do:
for my $bucket ($b->buckets()) {
  # for each item in the bucket do:
  for my $item ($bucket->items()) {
    print "Bucket ", $bucket->serial(), " - Item : $item\n";
    # make the directory unless it already exists
    mkdir($bucket->serial()) unless (-d $bucket->serial());
    # move the file with File::Copy::move
    File::Copy::move($item, $bucket->serial());
  }
}
