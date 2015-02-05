# -include TinyCompiler/Makefile  # - added ahead means igonoring error(can't find the file)

.PHONY: Debug Release

Debug:
	cd TinyCompiler
	make -f Makefile.Debug
	cd ..

Release:
	cd TinyCompiler
	make -f Makefile.Release
	cd ..



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
