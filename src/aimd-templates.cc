#include <cassert>
#include <utility>
#include <iostream>
#include "aimd.hh" 
using namespace std;

/* I am assuming this is going to be called as soon as packets_received
   is called */
template <class NextHop>
/*void Aimd::send( const unsigned int id, NextHop & next, const double & tickno )*/
//{
  //assert( _packets_sent >= _largest_ack + 1 );
  //while ( _packets_sent < _largest_ack + 1 + _the_window ) {
    //Packet p( id, _flow_id, tickno, _packets_sent );
    //_packets_sent++;
    //next.accept( p, tickno );
  //}
/*}*/
void Aimd::send(const unsigned int id, NextHop & next, const double & tickno,const unsigned int packets_sent_cap  )
{
//    cout<<"tickno="<<tickno<<"\tflow_id="<<_flow_id<<"\t_the_window="<<_the_window<<endl;
    assert( _packets_sent >= _largest_ack + 1);
    if( (_packets_sent - _largest_ack - 1 < _the_window) 
        and (_last_send_time + _inter_send_time <= tickno) ) {
        if( _packets_sent >= packets_sent_cap){return;}

        Packet p( id, _flow_id, tickno, _packets_sent );
        _packets_sent++;
        next.accept( p, tickno );
        _last_send_time = tickno;
    }
}
