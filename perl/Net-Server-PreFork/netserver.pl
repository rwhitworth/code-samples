use strict;
package tserv;

use base qw(Net::Server::PreFork);

use Data::Dumper qw(Dumper);

sub process_request 
{
  my $self = shift;
  $self->log(1, "someone connected!\n");
  # $self->log(1, Dumper($self->{server}));
  $self->log(1, "$self->{server}{peeraddr}:$self->{server}{peerport} connected\n");
  my $s = <STDIN>;
  if ($s =~ /.*12345.*/)
  {
    print "WINNER WINNER CHICKEN DINNER! Key: 0x12345678\n";
    $self->log(1, "WINNER!\n");
  }
  else
  {
    print "Sorry.\n";
  }
}

tserv->run(conf_file=>'netserver.conf');
# tserv->run(port=>7777);

1;
