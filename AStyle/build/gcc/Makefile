# Make file for GCC compiler on Linux or compatible OS

RM  = rm -f
CP  = cp -p
Q   = @

# list of source files for astyle
SRC = astyle_main.cpp \
      ASBeautifier.cpp \
      ASFormatter.cpp \
      ASEnhancer.cpp \
      ASLocalizer.cpp \
      ASResource.cpp

# list of source files for libraries without ASLocalizer
SRCx = astyle_main.cpp \
       ASBeautifier.cpp \
       ASFormatter.cpp \
       ASEnhancer.cpp \
       ASResource.cpp

# source directories
vpath %.cpp ../../src
vpath %.h   ../../src

# NOTE for java compiles the environment variable $JAVA_HOME must be set
# example: export JAVA_HOME=/usr/lib/jvm/java-6-sun-1.6.0.00
ifndef JAVA_HOME
    JAVA_HOME = /usr/lib/jvm/default-java
endif

# set prefix if not defined on the command line
ifndef prefix
    prefix=$(HOME)/usr
endif
SYSCONF_PATH=$(prefix)/share/doc/astyle

# define macros
# CXX defaults to g++
bindir = bin
objdir = obj
ipath=$(prefix)/bin
CBASEFLAGS = -Wall -Wextra -fno-rtti -fno-exceptions -std=c++11
JAVAINCS   = -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
INSTALL=install -o $(USER) -g $(USER)

# Library's major version number -- Increment in case of incompatible API
# change.
MAJORVER = 3
# Library's minor version number -- Increment when functionnality is added in a
# backward-compatible manner; reset to 0 when major number changes.
MINORVER = 2
# Library's patch version number -- Increment in case of backward-compatible
# bug fixes or refactoring; reset to 0 when minor number changes.
PATCHVER = 0
# Library's full version number.
SOLIBVER = $(MAJORVER).$(MINORVER).$(PATCHVER)

##################################################

# define compile options for each build
ifdef CFLAGS
    CFLAGSr   = -DNDEBUG $(CBASEFLAGS) $(CFLAGS)
    CFLAGSd   = -g $(CBASEFLAGS) $(CFLAGS)
else
    CFLAGSr   = -DNDEBUG -O3 $(CBASEFLAGS)
    CFLAGSd   = -g $(CBASEFLAGS)
endif
CFLAGSs   = -DASTYLE_LIB -fPIC $(CFLAGSr)
CFLAGSsd  = -DASTYLE_LIB -fPIC $(CFLAGSd)
CFLAGSa   = -DASTYLE_LIB $(CFLAGSr)
CFLAGSad  = -DASTYLE_LIB $(CFLAGSd)
CFLAGSsj  = -DASTYLE_JNI -fPIC $(CFLAGSr) $(JAVAINCS)
CFLAGSsjd = -DASTYLE_JNI -fPIC $(CFLAGSd) $(JAVAINCS)

# define link options
ifdef LDFLAGS
    LDFLAGSr   = $(LDFLAGS)
    LDFLAGSd   = $(LDFLAGS)
else
    LDFLAGSr   = -s
    LDFLAGSd   =
endif

# object files are built from the source list $(SRC)
# a suffix is added for each build
OBJ   = $(patsubst %.cpp,$(objdir)/%.o,$(SRC))
OBJd  = $(patsubst %.cpp,$(objdir)/%_d.o,$(SRC))
OBJs  = $(patsubst %.cpp,$(objdir)/%_s.o,$(SRCx))
OBJsd = $(patsubst %.cpp,$(objdir)/%_sd.o,$(SRCx))
OBJa  = $(patsubst %.cpp,$(objdir)/%_a.o,$(SRCx))
OBJad = $(patsubst %.cpp,$(objdir)/%_ad.o,$(SRCx))
OBJsj  = $(patsubst %.cpp,$(objdir)/%_sj.o,$(SRCx))
OBJsjd = $(patsubst %.cpp,$(objdir)/%_sjd.o,$(SRCx))

# define object file rule (with the suffix) for each build
HEADERS =       astyle.h astyle_main.h markdefs.h
# OBJ
$(objdir)/%.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSr) -c $< -o $@

# OBJd
$(objdir)/%_d.o: DEFS=$(DEFFS)
$(objdir)/%_d.o:  %.cpp  $(HEADERS)
	$(CXX) $(DEFS) $(CFLAGSd) -c $< -o $@

# OBJs
$(objdir)/%_s.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSs) -c $< -o $@

# OBJsd
$(objdir)/%_sd.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSsd) -c $< -o $@

# OBJa
$(objdir)/%_a.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSa) -c $< -o $@

# OBJad
$(objdir)/%_ad.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSad) -c $< -o $@

# OBJsj
$(objdir)/%_sj.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSsj) -c $< -o $@

# OBJsjd
$(objdir)/%_sjd.o:  %.cpp  $(HEADERS)
	$(CXX) $(CFLAGSsjd) -c $< -o $@

BIN  = astyle

##################################################
# define build dependencies for each command

release:  $(BIN)
astyle:  dirs $(OBJ)
	$(CXX) $(LDFLAGSr) -o $(bindir)/$@ $(OBJ)
	$(Q) echo

# debug:  $(BIN)d
astyled:  DEFFS = -DDBG
astyled: dirs $(OBJd)
	$(CXX) $(LDFLAGSd) -o $(bindir)/$@ $(OBJd)
	$(Q) echo

$(objdir) $(bindir) $(ipath) $(SYSCONF_PATH)/html:
	$(Q) [ -d $(@) ] || $(INSTALL) -m 755 -d $(@)

dirs: $(objdir) $(bindir)

shared:  libastyle.so
libastyle.so:  $(OBJs)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastyle.so.$(MAJORVER) \
	-o $(bindir)/libastyle.so.$(SOLIBVER) $^
	$(Q) ln  --symbolic --force  libastyle.so.$(SOLIBVER)  libastyle.so.$(MAJORVER)
	$(Q) ln  --symbolic --force  libastyle.so.$(MAJORVER)  libastyle.so
	$(Q) mv  libastyle.so*  $(bindir)/
	$(Q) echo

shareddebug:  libastyled.so
libastyled.so:  $(bindir) $(OBJsd)
	$(CXX) -shared $(LDFLAGSd) -Wl,-soname,libastyled.so.$(MAJORVER) \
	-o $(bindir)/libastyled.so.$(SOLIBVER) $^
	$(Q) ln  --symbolic --force  libastyled.so.$(SOLIBVER)  libastyled.so.$(MAJORVER)
	$(Q) ln  --symbolic --force  libastyled.so.$(MAJORVER)  libastyled.so
	$(Q) mv  libastyled.so*  $(bindir)/
	$(Q) echo

static:  libastyle.a
libastyle.a:  $(bindir) $(OBJa)
	ar crs $(bindir)/$@ $^
	$(Q) echo

staticdebug:  libastyled.a
libastyled.a:  $(bindir) $(OBJad)
	ar crs $(bindir)/$@ $^
	$(Q) echo

java:  libastylej.so
libastylej.so:  $(bindir) $(OBJsj)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastylej.so.$(MAJORVER) \
	-o $(bindir)/libastylej.so.$(SOLIBVER) $^
	$(Q) ln  --symbolic --force  libastylej.so.$(SOLIBVER)  libastylej.so.$(MAJORVER)
	$(Q) ln  --symbolic --force  libastylej.so.$(MAJORVER)  libastylej.so
	$(Q) mv  libastylej.so*  $(bindir)/
	$(Q) echo

javadebug:  libastylejd.so
libastylejd.so:  $(bindir) $(OBJsjd)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastylejd.so.$(MAJORVER) \
	-o $(bindir)/libastylejd.so.$(SOLIBVER) $^
	$(Q) ln  --symbolic --force  libastylejd.so.$(SOLIBVER)  libastylejd.so.$(MAJORVER)
	$(Q) ln  --symbolic --force  libastylejd.so.$(MAJORVER)  libastylejd.so
	$(Q) mv  libastylejd.so*  $(bindir)/
	$(Q) echo

all:  release debug shared shareddebug static staticdebug

javaall:  java javadebug

clean: cleanobj
	$(Q) $(RM)    $(bindir)/*astyle*
cleanobj:
	$(Q) $(RM)    $(objdir)/*.o
clobber: uninstall
	$(Q) $(RM) -r $(objdir) $(bindir)

prep-install:
	$(Q) [ ! -d $(SYSCONF_PATH)/html ] || $(RM) -r $(SYSCONF_PATH)/html

install_debug: BIN=astyled
install_debug: install

install: prep-install $(ipath) $(SYSCONF_PATH)/html
	$(Q) $(INSTALL) -m 755 $(bindir)/$(BIN)  $(ipath)

	@    for files in astyle.html \
                  install.html \
                  news.html \
                  notes.html \
                  styles.css; \
	do \
		$(INSTALL)  -m 644  ../../doc/$$files  $(SYSCONF_PATH)/html; \
	done

uninstall:
	$(Q) $(RM)     $(ipath)/$(BIN)
	$(Q) $(RM) -r  $(SYSCONF_PATH)

# copy release files to AStyleDev for testing
# --force, --preserve, --no-dereference (retain links)
testlibs:
	cp  -fpP  $(bindir)/astyle         ../../../AStyleDev/src-p/
	cp  -fpP  $(bindir)/libastyle.so*  ../../../AStyleDev/src-c/
	cp  -fpP  $(bindir)/libastyle.so*  ../../../AStyleDev/src-o/
	cp  -fpP  $(bindir)/libastyle.so*  ../../../AStyleDev/src-p/
	cp  -fpP  $(bindir)/libastyle.so*  ../../../AStyleDev/src-s/
	cp  -fpP  $(bindir)/libastyle.so*  ../../../AStyleDev/src-s2/
	cp  -fpP  $(bindir)/libastylej.so* ../../../AStyleDev/src-j/

# copy debug files to AStyleDev for testing
# --force, --preserve, --no-dereference (retain links)
testlibsd:
	cp  -fpP  $(bindir)/astyled         ../../../AStyleDev/src-p/
	cp  -fpP  $(bindir)/libastyled.so*  ../../../AStyleDev/src-c/
	cp  -fpP  $(bindir)/libastyled.so*  ../../../AStyleDev/src-o/
	cp  -fpP  $(bindir)/libastyled.so*  ../../../AStyleDev/src-p/
	cp  -fpP  $(bindir)/libastyled.so*  ../../../AStyleDev/src-s/
	cp  -fpP  $(bindir)/libastyled.so*  ../../../AStyleDev/src-s2/
	cp  -fpP  $(bindir)/libastylejd.so* ../../../AStyleDev/src-j/
