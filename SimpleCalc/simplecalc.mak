ifndef CFG
	CFG=debug
endif

CC=gcc
CFLAGS=-pthread -fPIC $(PLAT)
CXX=g++
CXXFLAGS=$(CFLAGS)
LD=$(CXX)
LDFLAGS:=$(CFLAGS)

ifeq "$(CFG)" "debug"
	CFLAGS+= -pipe -Wall -Wno-unknown-pragmas -Wno-unused -Wno-reorder -O0 -fexceptions -g -fstack-protector  -D_DEBUG
	target=SimpleCalcD
endif

ifeq "$(CFG)" "release"
	CFLAGS+= -pipe -Wall -Wno-unknown-pragmas -Wno-unused -Wno-reorder -O2 -fexceptions -g -fstack-protector  -DNDEBUG
	TARGET=SimpleCalcR
endif

.PHONY: all
all: $(target)

ifndef target
	@echo "无编译目标！unrecognized \$$CFG '$(CFG)'"
	@exit 1
endif

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
%.o: %.cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.d:%.c
	@set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ :/g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.d:%.cpp
	@set -e; rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ :/g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

util=main.cpp

sources=$(util)
objects=$(patsubst %.cxx,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(filter %.c %.cc %.cpp %.cxx,$(sources))))))

$(target):$(objects)
	mkdir -p "$(dir $(target))"
	$(CXX) $(CXXFLAGS) -o $@ $(objects)

.PHONY: clean
clean:
	-rm -f $(objects) $(target) *.d

-include $(sources:.cpp=.d)
