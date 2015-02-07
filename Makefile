# -include TinyCompiler/Makefile  # - added ahead means igonoring error(can't find the file)

#MAKE=make -C
#.PHONY: Debug Release
#
##default is debug
#Debug: 
#	$(MAKE) -C TinyCompiler
#	# cd TinyCompiler && make -f Makefile.Debug
#
#Release:
#	cd TinyCompiler && $(MAKE) -f Makefile.Release



# it has nothing about this program but just add it here
# multitargets character 
#   bigoutput littleoutput : text.g
#   generate text.g -$(subst output,,$@) > $@
#
#   equals to:
#
#   bigoutput : text.g
#   generate text.g -big > bigoutput
#   littleoutput : text.g
#   generate text.g -little > littleoutput
#
#
# static mode character
#   files = foo.elc bar.o lose.o
#   $(filter %.o,$(files)): %.o: %.c
#   $(CC) -c $(CFLAGS) $< -o $@
#   $(filter %.elc,$(files)): %.elc: %.el
#   emacs -f batch-byte-compile $<
#
#   equals to:
#
#   bar.o : bar.c
#   	$(CC) -c $(CFLAGS) bar.c -o bar.o
#   lose.o : lose.c
#   	$(CC) -c $(CFLAGS) lose.c -o lose.o
#   foo.elc : foo.el
#   	emacs -f batch-byte-compile foo.el
#
#
# notice
#   xxxx: xxxx
#   	cd aa
#   	pwd
#   (echo old)
#   is not the same as
#
#   xxxx: xxxx
#   	cd aa;  pwd
#   (echo aa)

ifndef JOBS
	JOBS=4
endif

.PHONY: all
all: \
	debug \
	release


.PHONY: debug
debug: \
	tinycompiler.debug \
	simplecalc.debug


.PHONY: release
release: \
	tinycompiler.release \
	simplecalc.release


tinycompiler.debug : 
	$(MAKE) -j$(JOBS) -C TinyCompiler/ -f tinycompiler.mak CFG="debug"

tinycompiler.release : 
	$(MAKE) -j$(JOBS) -C TinyCompiler/ -f tinycompiler.mak CFG="release"

simplecalc.debug : 
	$(MAKE) -j$(JOBS) -C SimpleCalc/ -f tinycompiler.mak CFG="debug"

simplecalc.release : 
	$(MAKE) -j$(JOBS) -C SimpleCalc/ -f tinycompiler.mak CFG="release"

.PHONY: clean
clean:
	$(MAKE) -C TinyCompiler/ -f tinycompiler.mak clean
	$(MAKE) -C SimpleCalc/ -f simplecalc.mak clean
