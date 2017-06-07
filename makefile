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
RECURSIVEDIRSEARCH 	= $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECURSIVEDIRSEARCH,$d/,$2))
ALLSRCS				:= $(call RECURSIVEDIRSEARCH,$(SRCDIR)/,*.$(SRCEXT))
EXCLDSRCS			:= src/3rdparty/gtest-all.cpp
FILTSRCS			:= $(filter-out $(EXCLDSRCS),$(ALLSRCS))
OBJS				:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(FILTSRCS:.$(SRCEXT)=.o))
LIBDIR				:= -Lc:/libs
LIBS				:= -lprism -lgtest
CPPFLAGS			:= -Wall
CFLAGS				:=
CXXFLAGS			:= -std=c++11
INCDIR				:= -I inc -I c:/inc
DEFINES				:= #-D

default : $(TARGET)

# =============================================================================================

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(BINDIR))

# build an executable
$(TARGET) : $(OBJS)
	@echo Building target: $@
	$(CC) $(OBJS) -o $(TARGET) $(LIBDIR) $(LIBS)
	@echo Finished building target: $@
	@echo ''

# build a shared library
shared : $(OBJS)
	@echo Building library: $(TARGET).$(TARGETEXT)
	$(CC) -shared -o $(TARGET).$(TARGETEXT) $(OBJS) $(LIBDIR) $(LIBS) $(DEFINES)
	@echo Finished building library: $(TARGET).$(TARGETEXT)
	@echo ''

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo Building file: $<
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
