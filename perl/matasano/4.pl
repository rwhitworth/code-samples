use strict;
use warnings;
use MIME::Base64;

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

sub hex2str
{
  my $str = shift;
  $str =~ s/([0-9A-Fa-f]{2})/chr(hex($1))/eg;
  return $str;
}

sub str2b64
{
  my $str = shift;
  return MIME::Base64::encode_base64($str);
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

my @a;
my @chars = ('A'..'Z','a'..'z', '0'..'9');
open(DAT, "<4.dat");
while (<DAT>)
{
  chomp;
  push @a, hex2str($_);
}

foreach my $x (@a)
{
  # print $x . "\n";
  foreach my $y (@chars)
  {
    my $un = xorstr($x, $y);
    if ((is_english($un) > 79) && (is_message($un))) { print "$y : " . is_message($un) . " : " . is_english($un) . " : $un\n"; }
  } 
}
