use Mojolicious::Lite;

# Simple plain text response
get '/' => {text => 'I like Mojolicious!'};

# Route associating "/time" with template in DATA section
get '/time' => 'clock';
#
# # RESTful web service with JSON and text representation
get '/list/:offset' => sub {
   my $self    = shift;
   my $numbers = [0 .. $self->param('offset')];
   $self->respond_to(
     json => {json => $numbers},
     txt  => {text => join(',', @$numbers)}
   );
};


# Scrape information from remote sites
post '/title' => sub {
  my $self = shift;
  my $url  = $self->param('url') || 'http://mojolicio.us';
  $self->render(
    text => $self->ua->get($url)->res->dom->at('title')->text);
};

# WebSocket echo service
websocket '/echo' => sub {
  my $self = shift;
  $self->on(message => sub {
    my ($self, $msg) = @_;
    $self->send("echo: $msg");
  });
};

app->start;
__DATA__

@@ clock.html.ep
% use Time::Piece;
% my $now = localtime;
The time is <%= $now->hms %>.
