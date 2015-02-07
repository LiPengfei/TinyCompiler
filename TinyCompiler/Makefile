CFLAGS=-g
tinycompile=TinyCompile

sources=util.c main.c scan.c parse.c analyze.c symtab.c cgen.c code.c

obj_util=util.o main.o
obj_scan=scan.o
obj_parse=parse.o
obj_analyze=analyze.o symtab.o
obj_codegen=cgen.o code.o

objects = $(obj_util) $(obj_scan) $(obj_parse) $(obj_analyze) $(obj_codegen)
vpath %.o ./obj             # if you can't find some .o file in current directory,
                            # find them in Debug. So I can mv o to Debug after my compiler

%.o: CFLAGS=-O
$(tinycompile): $(objects)
	$(CC) -o $(tinycompile) $(objects)
	chmod 555 $(tinycompile)
	-mv *.o obj/

$(sources:.c=.d):%.d:%.c
	set -e; rm -f $@;\
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ :/g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(sources:.c=.d)

.PHONY: clean
clean:
	-rm -f *.o TinyCompile *.d  # add '-' ahead means ignore errors to go on
	-rm -f ./obj/*.o        # add '-' ahead means ignore errors to go on
