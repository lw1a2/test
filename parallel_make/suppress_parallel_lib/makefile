BIN=a b c

CLEAN=$(BIN:%=%/clean)

all: $(BIN)
clean: $(CLEAN)

$(BIN)::
	cd $@ && $(MAKE)

$(CLEAN):
	cd $(@D) && $(MAKE) clean

.PHONY: all clean

