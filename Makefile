# Simple Makefile for your engine (hard-coded but reliable)

CC      := gcc
CFLAGS  := -g -O3 -Wall -Wextra -std=c17 -Iinclude -MMD -MP
LDFLAGS := -lglfw -lGL -lXrandr -lpthread -ldl -lm

SRCDIR  := srcs
BINDIR  := bins
GLAD_SRC := include/glad.c
GLAD_OBJ := $(BINDIR)/glad.o

# Find all .c sources under srcs/
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
# Map srcs/foo/bar.c -> bins/foo/bar.o
OBJS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

BIN := $(BINDIR)/engine

.PHONY: all clean run

all: $(BIN)

# Link the final engine binary
$(BIN): $(OBJS) $(GLAD_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) $(GLAD_OBJ) -o $@ $(LDFLAGS)

# Compile rule for source -> object
# srcs/some/thing.c -> bins/some/thing.o
$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build glad object (if you keep glad.c in include/)
$(GLAD_OBJ): $(GLAD_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Include dependency files if present (safe if empty)
-include $(DEPS)

# Run convenience
run: all
	./$(BIN)

clean:
	rm -rf $(BINDIR)


