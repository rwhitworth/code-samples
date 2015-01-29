# released under the GPL on 2004-07-21 - written by lithron@gmail.com
# http://www.lithron.com
# "md5sha.pl" version 0.01
# trust me, the code isn't anything special.
# I'm just building upon the work of giants.

use strict;
use Digest::MD5;
use Digest::SHA;

my $file = shift or die "usage: md5sha.pl filename\n";

print "filename, md5, sha\n";


open (FILE, $file) or die "Can't open '$file': $!";
binmode(FILE);
my $md5digest = Digest::MD5->new->addfile(*FILE)->hexdigest; 
my $shadigest = Digest::SHA->new->addfile(*FILE)->hexdigest;
close(FILE);

chomp($_);
print "\"$file\", $md5digest, $shadigest\n";

