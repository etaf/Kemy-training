#ifndef LINK_HH
#define LINK_HH
#include "kemyqueue.hh"

#include "packet.hh"
#include "delay.hh"

class Link
{
private:
  KemyQueue _buffer;
  double _forward_ppms;
  Delay _pending_packet;
  unsigned int _limit;

public:
  Link(WhiskerTree & whiskers,const bool  & s_track,const double & forward_ppms, const double s_rate,
	const unsigned int s_limit = std::numeric_limits<unsigned int>::max() )
    : _buffer(whiskers,s_track),_forward_ppms(forward_ppms), _pending_packet( 1.0 / s_rate ), _limit( s_limit ) {}

  void accept( const Packet & p, const double & tickno ) noexcept {
    if ( _pending_packet.empty() ) {
      _pending_packet.accept( p, tickno );
    } else {
        _buffer.enque(p,tickno);
      //if ( _buffer.size() < _limit ) {
        /*_buffer.push( p );*/
      }
  }

  template <class NextHop>
  void tick( NextHop & next, const double & tickno );

  double next_event_time( const double & tickno ) const { 
      return _pending_packet.next_event_time( tickno ); 
  }

};

#endif
