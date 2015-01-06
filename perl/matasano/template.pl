$|++;
use strict;
use warnings;
use MIME::Base64;
use Data::BitStream;

# http://en.wikipedia.org/wiki/Letter_frequencies
# ETAON RISHD LFCMU GYPWB VKJXQ Z
#              ^
#              First 12 characters, 80% of characters
#         ^
#         First 8 characters, 65% of characters
# Frequency:
# E 12.7%
# T  9.0%
# A  8.1%
# O  7.5%
# I  6.9%
# N  6.7%
# S  6.3%
# H  6.0%
# R  5.9%
#
# TH HE AN RE ER IN ON AT ND ST ES EN OF TE ED OR TI HI AS TO
# Most common double letter pairs
# LL EE SS OO TT FF RR NN PP CC
# Most common doubled letters
#
# First letters in a word:
# T 16.6%
# A 11.6%
# S  7.7%
# H  7.2%
# W  6.7%
# I  6.2%
# O  6.2%
# B  4.7%

sub str2hex
{
  my $str = shift;
  my @stra = ();
  my $res = '';
  my %escapes;
  for (0..255)
  {
    $escapes{chr($_)} = sprintf("%02X", $_);
  }
  @stra = $str =~ /./sg;
  foreach my $x (@stra)
  {
    $res = $res . $escapes{$x};
  }
  return lc $res;
}

sub str2hex_v2
{
  my $str = shift;
  return lc unpack("H*", $str);
}

sub hex2str
{
  my $str = shift;
  $str =~ s/([0-9A-Fa-f]{2})/chr(hex($1))/eg;
  return $str;
}

sub hex2str_v2
{
  my $str = shift;
  return pack("H*", $str);
}

sub str2b64
{
  my $str = shift;
  my $temp = MIME::Base64::encode_base64($str);
  chomp $temp;
  return $temp;
}

sub b642str
{
  my $str = shift;
  return MIME::Base64::decode_base64($str);
}

sub xorstr
{
  my $str = shift;
  my $xor = shift;
  if (length($str) != length($xor))
  {
    # print "str and xor not same length\n";
  }
  my $res = "";
  my $keycounter = 0;
  for my $char (split //, $str)
  {
    if ($keycounter >= length($xor)) { $keycounter = 0; } 
    my $key = ord(substr($xor, $keycounter, 1));
    $res .= chr(ord($char) ^ $key);
    $keycounter++;
  }
  return $res;
}

sub is_ascii
{
  my $str = shift;
  my $len = length($str);
  my $count = 0;
  my @a = split(//, $str);
  foreach my $x (@a)
  {
    $count++ unless (ord($x) > 127);
  }   
  if ($count == $len) { return 1; }
  return 0; 
}


sub is_message
{
  my $str = shift;
  my $len = length($str);
  my $count = 0;
  my @a = split(//, $str);
  foreach my $x (@a)
  {
    $count++ if ((ord($x) >= 32) && (ord($x) <= 126));
    $count++ if (ord($x) == 10);
    $count++ if (ord($x) == 13);
  }   
  if ($count == $len) { return 1; }
  return 0; 
}

sub is_english
{
  #returns a percent chance the string could be English
  my $str = shift;
  my $len = length($str);
  $str = lc $str;
  $str =~ s/\W//g;
  $str =~ s/\d//g;
  return int((length($str) / $len) * 100)
}

sub hammingcode
{
  my $str = shift;
  my $str2 = shift;
  my $bs = Data::BitStream->new();
  my $bs2 = Data::BitStream->new();
  $bs->from_raw($str);
  $bs2->from_raw($str2);
  my $bin = $bs->to_string();
  my $bin2 = $bs2->to_string();
  my $len = length($bin);
  $len = length($bin2) if ($len > length($bin2));
  my $count = 0;
  for my $x (1..$len)
  {
    $count++ unless (substr($bin, $x, 1) eq substr($bin2, $x, 1));
  }
  return $count;
}

sub hammingtest
{
  print hammingcode('A', 'B') . " : 2\n";
  print hammingcode('a', 'c') . " : 1\n";
  print hammingcode('a', 'd') . " : 2\n";
  print hammingcode('a', 'f') . " : 3\n";
}


my $str = '';
my $bstr = '';
open(DAT, "<6.dat");
while (<DAT>)
{
  chomp;
  $str = $str . $_;
}

$bstr = b642str($str);
my $short = substr($bstr, 0, 400);

for my $x (2..60)
{
  if (length($bstr) % $x == 0) { print "$x\n"; }
}
print "len: " . length($bstr) . "\n";

my $a = 0;
my $b = 0;
my $c = 0;
my $hdist;
for my $x (3..60)
{
  $a = '';
  $b = '';
  $c = '';
  $hdist = 0;
  my $looptemp = int length($bstr) / $x;
  $looptemp--;
  for my $y (0..$looptemp)
  {
    $a = $a . substr($bstr, $y * $x, 1);
    $b = $b . substr($bstr, ($y * $x) + 1, 1);
    $c = $c . substr($bstr, ($y * $x) + 2, 1);
    $hdist = hammingcode($a, $b);
    $hdist = $hdist + hammingcode($b, $c);
    $hdist = int($hdist / $x);
    # print "$x : $hdist\n";
  }
    print "$x : $hdist\n";
}
