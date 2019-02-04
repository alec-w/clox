# Setup for generating dependencies
DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

# Binary file
BIN := clox

# Source file directory
SRCDIR := .
# Header file directory
INCDIR := ../includes
# Object file directory
OBJDIR := ./obj
$(shell mkdir -p $(OBJDIR))
# Bin directory
BINDIR := ../bin
$(shell mkdir -p $(BINDIR))

# Compilation options
CC = gcc
CFLAGS = -I$(INCDIR)

# Source files
SRCS := $(wildcard $(SRCDIR)/*.c)

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@
LINK.c = $(CC) $(CFLAGS) $(LDFLAGS)

$(BIN): $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(patsubst %,$(OBJDIR)/%.o,$(basename $(notdir $(SRCS))))
	$(LINK.c) $(OUTPUT_OPTION) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;

.PHONY: clean
clean:
	rm -f $(BINDIR)/* $(OBJDIR)/*.o $(DEPDIR)/*.d

ALLDEPS := $(patsubst %,$(DEPDIR)/%.d,$(basename $(notdir $(SRCS))))

build-deps: $(ALLDEPS)
.PHONY: build-deps

include $(wildcard $(ALLDEPS))

