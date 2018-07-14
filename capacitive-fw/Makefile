ifneq ($(V), 1)
MFLAGS += --no-print-dir
Q := @
endif

all:
	$(Q)$(MAKE) $(MFLAGS) -C src

lib:
	$(Q)$(MAKE) $(MFLAGS) -C libopencm3 lib

clean:
	$(Q)$(MAKE) $(MFLAGS) -C libopencm3 $@
	$(Q)$(MAKE) $(MFLAGS) -C src $@

