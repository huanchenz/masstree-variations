CC = gcc
CXX = g++ -std=gnu++0x
CFLAGS = -g -O2 -fPIC
DEPSDIR := masstree/.deps
DEPCFLAGS = -MD -MF $(DEPSDIR)/$*.d -MP
MEMMGR = -ltcmalloc_minimal

all: hybridTest

hybridTest.o: hybridTest.cpp masstree/config.h $(DEPSDIR)/stamp
	$(CXX) $(CFLAGS) $(DEPCFLAGS) -include masstree/config.h -c -o hybridTest.o hybridTest.cpp

hybridTest: hybridTest.o masstree/mtIndexAPI.a
	$(CXX) $(CFLAGS) -o hybridTest hybridTest.o masstree/mtIndexAPI.a $(MEMMGR) -lpthread -lm

clean:
	$(RM) hybridTest *.o *~
