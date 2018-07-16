DEVICE = stm32f070c6t6
OPENCM3_DIR = ../libopencm3
OBJS += main.o trig.o

CPPFLAGS += -Os -Wall -Werror
LDFLAGS         += -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: clean all

all: sensor.elf sensor.hex

clean:
	$(Q)$(RM) -rf sensor.* *.o

flash: sensor.hex
	openocd -f ../capacitive.cfg "-c init; reset; halt; program sensor.hex verify; reset; resume; exit"

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk
