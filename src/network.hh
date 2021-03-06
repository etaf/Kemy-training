#ifndef NETWORK_HH
#define NETWORK_HH

#include <string>

#include "sendergangofgangs.hh"
#include "link.hh"
#include "delay.hh"
#include "receiver.hh"
#include "random.hh"
#include "answer.pb.h"
#include "whiskertree.hh"
class NetConfig
{
public:
  double mean_on_duration, mean_off_duration;
  unsigned int num_senders;
  double forward_ppms;
  double inter_send_time;
  double link_ppt;
  double delay;

  NetConfig( void )
    : mean_on_duration( 5000.0 ),
      mean_off_duration( 5000.0 ),
      num_senders( 8 ),
      forward_ppms( 1.0 ),
      inter_send_time(1.0 ),
      link_ppt( 1.0 ),
      delay( 150 )
  {}

  NetConfig( const KemyBuffers::NetConfig & dna )
    : mean_on_duration( dna.mean_on_duration() ),
      mean_off_duration( dna.mean_off_duration() ),
      num_senders( dna.num_senders() ),
      forward_ppms( dna.forward_ppms()),
      inter_send_time( dna.inter_send_time()),
      link_ppt( dna.link_ppt() ),
      delay( dna.delay() )
  {}

  NetConfig & set_link_ppt( const double s_link_ppt ) { link_ppt = s_link_ppt; return *this; }
  NetConfig & set_delay( const double s_delay ) { delay = s_delay; return *this; }
  NetConfig & set_num_senders( const unsigned int n ) { num_senders = n; return *this; }
  NetConfig & set_on_duration( const double & duration ) { mean_on_duration = duration; return *this; }
  NetConfig & set_off_duration( const double & duration ) { mean_off_duration = duration; return *this; }
  NetConfig & set_forward_ppms( const double & _forward_ppms) { forward_ppms = _forward_ppms; return *this;}
  NetConfig & set_inter_send_time( const double & tt) { inter_send_time = tt; return *this;}

  KemyBuffers::NetConfig DNA( void ) const
  {
      KemyBuffers::NetConfig ret;
      ret.set_mean_on_duration( mean_on_duration );
      ret.set_mean_off_duration( mean_off_duration );
      ret.set_num_senders( num_senders );
      ret.set_delay( delay );
      ret.set_link_ppt( link_ppt );

      return ret;
  }

  std::string str( void ) const
  {
    char tmp[ 256 ];
    snprintf( tmp, 256, "mean_on=%f, mean_off=%f, nsrc=%d, link_ppt=%f, delay=%f, forward_ppms=%f, inter_send_time=%f\n",
	      mean_on_duration, mean_off_duration, num_senders, link_ppt, delay ,forward_ppms, inter_send_time);
    return tmp;
  }
};

template <class SenderType1, class SenderType2>
class Network
{
private:
  PRNG & _prng;
  SenderGangofGangs<SenderType1, SenderType2> _senders;
  Link _link;
  Delay _delay;
  Receiver _rec;

  double _tickno;

  void tick( void );

public:
  Network( Link link, const SenderType1 & example_sender1, const SenderType2 & example_sender2, PRNG & s_prng, const NetConfig & config );

  Network( Link link, const SenderType1 & example_sender1, PRNG & s_prng, const NetConfig & config );

  void run_simulation( const double & duration );

  const SenderGangofGangs<SenderType1,SenderType2> & senders( void ) const { return _senders; }
};

#endif
