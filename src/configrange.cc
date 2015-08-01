#include "configrange.hh"

using namespace std;

static KemyBuffers::Range pair_to_range( const pair< double, double > & p )
{
  KemyBuffers::Range ret;
  ret.set_low( p.first );
  ret.set_high( p.second );
  return ret;
}

KemyBuffers::ConfigRange ConfigRange::DNA( void ) const

{
  KemyBuffers::ConfigRange ret;
  ret.mutable_link_packets_per_ms()->CopyFrom( pair_to_range( link_packets_per_ms ) );
  ret.mutable_rtt()->CopyFrom( pair_to_range( rtt_ms ) );
  ret.mutable_num_senders()->CopyFrom( pair_to_range( make_pair( min_senders, max_senders ) ) );
  ret.mutable_forward_ppms()->CopyFrom( pair_to_range( forward_ppms ) );
  ret.mutable_inter_send_time()->CopyFrom( pair_to_range( inter_send_time ) ); 

  ret.set_mean_off_duration( mean_off_duration );
  ret.set_mean_on_duration( mean_on_duration );

  return ret;
}
