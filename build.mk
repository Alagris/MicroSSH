TARGET ?= server
#############
#tools/commands
#############
CC=gcc
LD=gcc
#############
#flags
#############
CC_FLAGS=-c -I $(SRCDIR) -I common 
LD_FLAGS=-I $(SRCDIR) -I common 
#############
#directories
#############
SRCDIR?=$(TARGET)
BUILDDIR=build
LOGDIR=log
OBJDIR=$(BUILDDIR)/obj
#############
#suffixes
#############
C_SRC_SFX=c
C_OBJ_SFX=o
BIN_SFX=bin
#############
#file lists
#############
C_SOURCES := $(shell find $(SRCDIR) -name '*.$(C_SRC_SFX)') $(shell find common -name '*.$(C_SRC_SFX)')
C_OBJECTS = $(addprefix $(OBJDIR)/,$(C_SOURCES:.$(C_SRC_SFX)=.$(C_OBJ_SFX)))
#############
#names
#############
BINARY_NAME?=$(TARGET)
#############
#files
#############
BINARY_FILE=$(BUILDDIR)/$(BINARY_NAME).$(BIN_SFX)
#############
#make instructions
#############

$(BINARY_FILE): $(C_OBJECTS) $(OBJDIR)
	$(LD) $(LD_FLAGS)  $(C_OBJECTS) -o $@

# $(OBJDIR)/%.$(C_OBJ_SFX): $(SRCDIR)/%.$(C_SRC_SFX) $(OBJDIR)
# 	$(CC) $(CC_FLAGS)  $< -o $@

$(OBJDIR)/%.$(C_OBJ_SFX): %.$(C_SRC_SFX) $(OBJDIR)
	mkdir -p `dirname $@ `	&& \
	$(CC) $(CC_FLAGS)  $< -o $@

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)
