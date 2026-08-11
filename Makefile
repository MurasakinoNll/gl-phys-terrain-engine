CC      := gcc
CFLAGS  := -g -O3 -Wall -Wextra -std=c17 -Iinclude -MMD -MP $(shell pkg-config --cflags freetype2)
LDFLAGS := -lglfw -lGL -lXrandr -lpthread -ldl -lm $(shell pkg-config --libs freetype2)

SRCDIR  := srcs
BINDIR  := bins
GLAD_SRC := include/glad.c
GLAD_OBJ := $(BINDIR)/glad.o
STB_SRC := include/stb/stb_image.c
STB_OBJ := $(BINDIR)/stb/stb_image.o

SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
OBJS := $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

BIN := $(BINDIR)/engine

.PHONY: all clean run

all: $(BIN)

$(BIN): $(OBJS) $(GLAD_OBJ) $(STB_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) $(GLAD_OBJ) $(STB_OBJ) -o $@ $(LDFLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
$(GLAD_OBJ): $(GLAD_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(STB_OBJ): $(STB_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

run: all
	./$(BIN)

clean:
	rm -rf $(BINDIR)

