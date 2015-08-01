#ifndef AIMD_HH
#define AIMD_HH

#include <cassert>
#include <vector>
#include <string>
#include <limits>
#include "packet.hh"

class Aimd
{
private:
  int _packets_sent, _packets_received;
  /* _the_window is the congestion window */
  double _the_window;
  unsigned int _flow_id;
  static constexpr double INITIAL_WINDOW = 1.0; /* INITIAL WINDOW OF 1 */

  /* Largest ACK so far */
  int _largest_ack;

  /* Are we in Slow Start? */
  bool _slow_start;

  /* Track multiple losses within a window, DCCP style (RFC 4341 Page 6) */
  double _last_loss;
  double _rtt_at_loss;
  double _last_send_time;
  double _inter_send_time;
  bool _track;
public:
  Aimd(const double inter_send_time = 1,const bool s_track = false);

  void packets_received( const std::vector< Packet > & packets );
  void reset( const double & tickno ); /* start new flow */

  template <class NextHop>
  void send( const unsigned int id, NextHop & next, const double & tickno,
          const unsigned int packets_sent_cap = std::numeric_limits<unsigned int>::max()  );

  Aimd & operator=( const Aimd & ) { assert( false ); return *this; }

  double next_event_time( const double & tickno ) const;
};

#endif
