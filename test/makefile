CC=gcc
C_FLAGS = -g -Wall -Wextra  
TARGETS=daytimetcpcli
TARGETS_FILE=$(TARGETS).c

all:$(TARGETS)

clean:
	rm -f $(TARGETS) *.o

$(TARGETS):$(TARGETS_FILE)
	$(CC) $(C_FLAGS) $(TARGETS_FILE) -o $@
