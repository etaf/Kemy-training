#include <boost/functional/hash.hpp>
#include <vector>
#include <cassert>

#include "memory.hh"

using namespace std;

static const double alpha = 0.5;

void Memory::packet_drop(const double& tickno,const unsigned int & qlen)
{
    _ewma_qlen = (1 - alpha) * _ewma_qlen + alpha * qlen;

    _last_rec_time = tickno;

}
void Memory::packet_receive(const double& tickno,const unsigned int & qlen)
{
    _ewma_qlen = (1-alpha) * _ewma_qlen + alpha * qlen;

    _last_rec_time = tickno;

}
string Memory::str( void ) const
{
  char tmp[ 256 ];
  snprintf( tmp, 256, "ewma_qlen=%f", _ewma_qlen);
  return tmp;
}

const Memory & MAX_MEMORY( void )
{
  static const Memory max_memory( { 163840 } );
  return max_memory;
}

KemyBuffers::Memory Memory::DNA( void ) const
{
  KemyBuffers::Memory ret;
  ret.set_ewma_qlen( _ewma_qlen );
  return ret;
}

/* If fields are missing in the DNA, we want to wildcard the resulting rule to match anything */
#define get_val_or_default( protobuf, field, limit ) \
  ( (protobuf).has_ ## field() ? (protobuf).field() : (limit) ? 0 : 163840 )

Memory::Memory( const bool is_lower_limit, const KemyBuffers::Memory & dna )
  : _ewma_qlen( get_val_or_default( dna, ewma_qlen, is_lower_limit ) ),
    _last_rec_time(0 )
{
}

size_t hash_value( const Memory & mem )
{
  size_t seed = 0;
  boost::hash_combine( seed, mem._ewma_qlen );
  return seed;
}
