# Make file for GCC compiler on Linux or compatible OS

RM  = rm -f
CP  = cp -p

# list of source files for libraries without ASLocalizer
SRCx =  astyle_main.cpp \
        ASBeautifier.cpp \
        ASFormatter.cpp \
        ASEnhancer.cpp \
        ASResource.cpp

# list of source files for astyle
SRC = $(SRCx) ASLocalizer.cpp
SRC_ROOTS      = $(SRC:%.cpp=%)

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
    prefix=$(HOME)
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

OBJS_REGULAR            = ${addsuffix .o,$(SRC_ROOTS)}
AFFIX_a                 = ${addsuffix _a,$(SRC_ROOTS)}
AFFIX_s                 = ${addsuffix _s,$(SRC_ROOTS)}
AFFIX_sj                = ${addsuffix _sj,$(SRC_ROOTS)}
AFFIX_ALL               = $(AFFIX_a) $(AFFIX_s) $(AFFIX_sj)
AFFIX_dbg               = ${addsuffix d.o,$(AFFIX_ALL)}
AFFIX_objs              = ${addsuffix  .o,$(SRC_ROOTS) $(AFFIX_ALL)}
OBJS                    = ${addprefix $(objdir)/,$(AFFIX_objs) $(AFFIX_dbg)}

#
# Rule to make directories so each
# target does not need to mkdir anything.
#
$(OBJS):  $(objdir)
$(SYSCONF_PATH) $(ipath) $(bindir) $(objdir):
	$(INSTALL) -m 755 -d $@

${addsuffix .o,$(SRC_ROOTS)}: astyle_main.h
$(OBJS): %.cpp astyle.h
	@echo "Compile object %@ %%"

# define object file rule (with the suffix) for each build

## # OBJ
## $(objdir)/%.o:  %.cpp  astyle.h  astyle_main.h
## 	$(CXX) $(CFLAGSr) -c $< -o $@

## # OBJd
## $(objdir)/%_d.o: DEFS=$(DEFS)
## $(objdir)/%_d.o:  %.cpp  astyle.h  astyle_main.h
## 	$(CXX) -D$(DEFS) $(CFLAGSd) -c $< -o $@

## # OBJs
## $(objdir)/%_s.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSs) -c $< -o $@

## # OBJsd
## $(objdir)/%_sd.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSsd) -c $< -o $@

## # OBJa
## $(objdir)/%_a.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSa) -c $< -o $@

## # OBJad
## $(objdir)/%_ad.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSad) -c $< -o $@

## # OBJsj
## $(objdir)/%_sj.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSsj) -c $< -o $@

## # OBJsjd
## $(objdir)/%_sjd.o:  %.cpp  astyle.h
## 	$(CXX) $(CFLAGSsjd) -c $< -o $@
LIBASTYLE               = libastyle
LIBASTYLE_SHARED        =
LIBASTYLE_SHARED_DBG    =
LIBASTYLE_ARCHIVE       =
LIBASTYLE_ARCHIVE_DBG   =

BIN  = astyle
##################################################
# define build dependencies for each command

release:  astyle
astyle:  $(OBJ)
	$(CXX) $(LDFLAGSr) -o $(bindir)/$@ $^
	@ echo

debug:  astyled
astyled:  DEFS="-DDBG"
astyled:  $(OBJd)
	@echo "=====================" >&2
	$(CXX) $(LDFLAGSd) -o $(bindir)/$@ $^
	@ echo

shared:  libastyle.so
libastyle.so:  $(OBJs)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastyle.so.$(MAJORVER) \
	-o $(bindir)/libastyle.so.$(SOLIBVER) $^
	@ln  --symbolic --force  libastyle.so.$(SOLIBVER)  libastyle.so.$(MAJORVER)
	@ln  --symbolic --force  libastyle.so.$(MAJORVER)  libastyle.so
	@mv  libastyle.so*  $(bindir)/
	@ echo

shareddebug:  libastyled.so
libastyled.so:  $(OBJsd)
	$(CXX) -shared $(LDFLAGSd) -Wl,-soname,libastyled.so.$(MAJORVER) \
	-o $(bindir)/libastyled.so.$(SOLIBVER) $^
	@ln  --symbolic --force  libastyled.so.$(SOLIBVER)  libastyled.so.$(MAJORVER)
	@ln  --symbolic --force  libastyled.so.$(MAJORVER)  libastyled.so
	@mv  libastyled.so*  $(bindir)/
	@ echo

static:  libastyle.a
libastyle.a:  $(OBJa)
	ar crs $(bindir)/$@ $^
	@ echo

staticdebug:  libastyled.a
libastyled.a:  $(OBJad)
	ar crs $(bindir)/$@ $^
	@ echo

java:  libastylej.so
libastylej.so:  $(OBJsj)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastylej.so.$(MAJORVER) \
	-o $(bindir)/libastylej.so.$(SOLIBVER) $^
	@ln  --symbolic --force  libastylej.so.$(SOLIBVER)  libastylej.so.$(MAJORVER)
	@ln  --symbolic --force  libastylej.so.$(MAJORVER)  libastylej.so
	@mv  libastylej.so*  $(bindir)/
	@ echo

javadebug:  libastylejd.so
libastylejd.so:  $(OBJsjd)
	$(CXX) -shared $(LDFLAGSr) -Wl,-soname,libastylejd.so.$(MAJORVER) \
	-o $(bindir)/libastylejd.so.$(SOLIBVER) $^
	@ln  --symbolic --force  libastylejd.so.$(SOLIBVER)  libastylejd.so.$(MAJORVER)
	@ln  --symbolic --force  libastylejd.so.$(MAJORVER)  libastylejd.so
	@mv  libastylejd.so*  $(bindir)/
	@ echo

all:  release debug shared shareddebug static staticdebug

javaall:  java javadebug

cleanbinary:
	@rm -f $(ipath)/$(BIN)

clean: cleanbinary
	@rm -f $(objdir)/*.o $(bindir)/*astyle*

cleanobj:
	@rm -f $(objdir)/*.o

clobber: clean
	@$(RM) -r $(objdir) $(bindir)

#
# Ensure all the necessary dirs are in place.
install: $(SYSCONF_PATH) $(ipath) $(bindir)

install:
	$(INSTALL) -m 755 $(bindir)/$(BIN)  $(ipath)

	@if [ -d $(SYSCONF_PATH)/html ]; then \
		rm -rf  $(SYSCONF_PATH)/html; \
	fi

	$(INSTALL) -m 755 -d $(SYSCONF_PATH)
	@mkdir -p $(SYSCONF_PATH)/html;
	@for files in astyle.html \
                  install.html \
                  news.html \
                  notes.html \
                  styles.css; \
	do \
		$(INSTALL)  -m 644  ../../doc/$$files  $(SYSCONF_PATH)/html; \
	done

uninstall:
	rm -f $(ipath)/astyle
	rm -rf $(SYSCONF_PATH)

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
