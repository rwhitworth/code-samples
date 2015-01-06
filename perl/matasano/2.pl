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
    print "str and xor not same length\n";
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


my $str = hex2str('1c0111001f010100061a024b53535009181c');
my $xor = hex2str('686974207468652062756c6c277320657965');
my $output = xorstr($str, $xor);
print str2hex($output);
