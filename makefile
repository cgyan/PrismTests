# =============================================================================================
# Makefile
# makefile should be in the project root directory
# =============================================================================================


CC 					:= g++
PROJDIR				:= $(shell pwd)
SRCDIR 				:= src
BUILDDIR			:= build
BINDIR				:= bin
TARGETEXT			:=
TARGET				:= $(BINDIR)/runner
SRCEXT 				:= cpp
LIBDIR				:= -Lc:/libs
LIBS				:= -lprism -lgtest
CPPFLAGS			:= -Wall
CFLAGS				:=
CXXFLAGS			:= -std=c++11
INCDIR				:= -I inc -I c:/inc
DEFINES				:= #-D

default : $(TARGET)

# =============================================================================================

RECURSIVEDIRSEARCH = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECURSIVEDIRSEARCH,$d/,$2))

SRCS	:= # SRCS is filled in by src subfolder's module.mk files
OBJS 	= $(patsubst $(SRCDIR)/%.$(SRCEXT),$(BUILDDIR)/%.o,$(SRCS))

SUBMK 	:= $(call RECURSIVEDIRSEARCH,$(SRCDIR)/,*.mk)
-include $(SUBMK)

# build an executable
$(TARGET) : $(OBJS)
	@echo Building target: $@
	@mkdir -p $(BINDIR)
	$(CC) $(OBJS) -o $(TARGET) $(LIBDIR) $(LIBS)
	@echo Finished building target: $@
	@echo ''

# build a shared library
shared : $(OBJS)
	@echo Building library: $(TARGET).$(TARGETEXT)
	@mkdir -p $(BINDIR)
	$(CC) -shared -o $(TARGET).$(TARGETEXT) $(OBJS) $(LIBDIR) $(LIBS) $(DEFINES)
	@echo Finished building library: $(TARGET).$(TARGETEXT)
	@echo ''

# build an *.o file from a source file
$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@echo Building file: $<
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $(INCDIR) $(DEFINES) -MMD -c $< -o $@
	@echo Finished building file: $<
	@echo ''

clean :
	rm -rf build bin/*

cleaner : clean
	rm -rf bin

# scans each subdirectory from $(BUILDDIR) downwards looking for all generated
# dependency files then includes those files in the makefile
GENERATEDDEPENDENCIES := $(call RECURSIVEDIRSEARCH,$(BUILDDIR)/,*.d)
-include $(GENERATEDDEPENDENCIES)
