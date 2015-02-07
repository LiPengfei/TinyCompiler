ifndef CFG
	CFG=debug
endif

CC=gcc
CFLAGS=-pthread -fPIC $(PLAT)
CXX=g++
CXXFLAGS=$(CFLAGS)
LD=$(CXX)
LDFLAGS:=$(CFLAGS)
AR=ar
ARFLAGS=rcs

ifeq "$(CFG)" "debug"
	CFLAGS+= -pipe -Wall -Wno-unknown-pragmas -Wno-unused -Wno-reorder -O0 -fexceptions -g -fstack-protector  -D_DEBUG  -I. -I../include -I../include/devbase -I../../base/include -I../../devenv/include
	# TARGET=../lib/debug/libdevbased.a
	target=TinyCompilerD
endif

ifeq "$(CFG)" "release"
	CFLAGS+= -pipe -Wall -Wno-unknown-pragmas -Wno-unused -Wno-reorder -O2 -fexceptions -g -fstack-protector  -DNDEBUG  -I. -I../include -I../include/devbase -I../../base/include -I../../devenv/include
	# TARGET=../lib/release/libdevbase.a
	TARGET=TinyCompilerR
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
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ :/g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

util=util.c main.c
scan=scan.c
parse=parse.c
analyze=analyze.c symtab.c
codegen=cgen.c code.c

sources=$(util) $(scan) $(parse) $(analyze) $(codegen) 
objs=$(patsubst %.cxx,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(filter %.c %.cc %.cpp %.cxx,$(sources))))))

$(target):$(objs)
	mkdir -p "$(dir $(target))"
	$(CXX) $(CXXFLAGS) -o $@ $(objs)

.PHONY: clean
clean:
	-rm -f $(objs) $(target) *.d

-include $(sources:.c=.d)
