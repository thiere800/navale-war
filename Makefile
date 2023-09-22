CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lcunit
OBJDIR = obj
BINDIR = bin
SRCDIR = src
TESTDIR = tests

SOURCES = $(wildcard $(SRCDIR)/*.c)
TEST_SOURCES = $(wildcard $(TESTDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(TEST_SOURCES))

BAD_OBJECTS = $(filter-out $(OBJDIR)/main.o,$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)))

TARGET = $(BINDIR)/bataille_navale
TEST_TARGET = $(BINDIR)/test_bataille_navale

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(BAD_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(TEST_OBJECTS) $(filter-out $(OBJDIR)/main.o,$(OBJECTS))

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(TARGET)
	rm -f $(TEST_TARGET)

.PHONY: all clean test
