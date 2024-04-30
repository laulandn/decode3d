
LIBNAME=$(shell basename $(shell pwd))
LDNAME=lib$(LIBNAME)_static.a

####################################################################
# Makefile
####################################################################

PATH_TO_BASE=.

include $(PATH_TO_BASE)/../Makefile.target
include $(PATH_TO_BASE)/../Makefile.common

EXTRA_FLAGS=-I$(PATH_TO_BASE) -I.. -DNICK_USE_DECODE3D -DNICK_USE_NICK3D
EXTRA_LDFLAGS=-L$(PATH_TO_BASE)


###################################################################
# Our objects
###################################################################

PROGRAMS=
DIRS=$(wildcard */)
OBJS=$(subst .cpp,.$(OFILE),$(wildcard *.cpp))


####################################################################
# The libraries and programs 
####################################################################


####################################################################
# The targets 
####################################################################

all:	$(LDNAME)
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) all;)

$(LDNAME):	$(OBJS)
	$(AR_CMD) $(OBJS)
	$(RANLIB_CMD) $(LDNAME) 


clean:
	rm -rf *.$(OFILE) *.$(AFILE) *.s *.bak *.log map.f build *Data *.pdb $(PROGRAMS) *.exe *.exe.so *68k *.SYM .DS_Store *.ilk .gdb_history .nautilus-metafile.xml resource.frk RESOURCE.FRK finder.dat FINDER.DAT ._* */._* */*/._* */*/*/._* *~ */*~ */*/*~ */*/*/*~ *.class *.javap *.java.* *.h.? tmp/*
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) clean;)


fix: fix_perm fix_type
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) fix;)


install: all
	cp *.a /usr/local/lib
	mkdir /usr/local/include/$(LIBNAME)
	cp *.h /usr/local/include/$(LIBNAME)
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) install;)


# The different Libraries and Programs...


# dependencies
# NOTE: its ok to see errors when running makedepend
depend: remove_depends
	makedepend $(DEPENDFLAGS) *.cpp
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -i -C $(DIR) depend;)


remove_depends:
	rm -f Makefile.dep
	touch Makefile.dep
# Libraries...
	$(foreach DIR,$(DIRS),$(MAKE) -ik -C $(DIR) remove_depends;)


include $(PATH_TO_BASE)/../Makefile.tail


include Makefile.dep


# DO NOT DELETE
