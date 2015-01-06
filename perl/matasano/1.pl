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
  return $res;
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
  my $temp = MIME::Base64::encode_base64($str);
  chomp $temp;
  return $temp; # MIME::Base64::encode_base64($str);

}

sub b642str
{
  my $str = shift;
  return MIME::Base64::decode_base64($str);
}

print 'hex str: ' . hex2str('49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d') . "\n";
print 'hex str: ' . str2hex("I'm killing your brain like a poisonous mushroom") . "\n";
print 'b64 str: ' . str2b64("I'm killing your brain like a poisonous mushroom") . "\n";
print '    str: ' . b642str(str2b64("I'm killing your brain like a poisonous mushroom")) . "\n";
