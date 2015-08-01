AM_CPPFLAGS = -I../protobufs
AM_CXXFLAGS = $(PICKY_CXXFLAGS)
LDADD = ../protobufs/libkemyprotos.a -ljemalloc -lm $(protobuf_LIBS)

bin_PROGRAMS = kemy rat-runner scoring-example

common_source = delay.hh evaluator.cc evaluator.hh                 \
	exponential.hh link.hh link-templates.cc                       \
	memory.cc memory.hh memoryrange.cc memoryrange.hh              \
	network.cc network.hh packet.hh poisson.hh                     \
	random.cc random.hh            								   \
	receiver.cc receiver.hh sendergang.cc sendergang.hh            \
        sendergangofgangs.cc sendergangofgangs.hh                  \
	utility.hh whisker.cc whisker.hh whiskertree.cc whiskertree.hh \
	aimd-templates.cc aimd.cc aimd.hh                              \
        configrange.hh configrange.cc                              \
	kemyqueue.hh kemyqueue.cc

kemy_SOURCES = $(common_source) kemy.cc ratbreeder.cc ratbreeder.hh 

rat_runner_SOURCES = $(common_source) rat-runner.cc

scoring_example_SOURCES = $(common_source) scoring-example.cc
