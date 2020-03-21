CONFIG_MODULE_SIG = n
TARGET_MODULE := fibdrv

BIGNUM_DIR := bignum

obj-m := $(TARGET_MODULE).o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

GIT_HOOKS := .git/hooks/applied

all: $(GIT_HOOKS) bignum client
	$(MAKE) -I$(PWD)/$(BIGNUM_DIR) -C $(KDIR) M=$(PWD) modules

.PHONY: bignum

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) client out ./bignum/bignum.o
load:
	sudo insmod $(TARGET_MODULE).ko
unload:
	sudo rmmod $(TARGET_MODULE) || true >/dev/null

client: client.c
	$(CC) -o $@ $^

bignum: $(BIGNUM_DIR)/bignum.c
	@echo "bignum make test...."
	$(CC) -c -I$(BIGNUM_DIR) -o $(BIGNUM_DIR)/bignum.o $(BIGNUM_DIR)/bignum.c

stch:
	@echo "MSG"

PRINTF = env printf
PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m
pass = $(PRINTF) "$(PASS_COLOR)$1 Passed [-]$(NO_COLOR)\n"

check: all
	$(MAKE) unload
	$(MAKE) load
	sudo ./client > out
	$(MAKE) unload
	@diff -u out bignum/expected.txt && $(call pass)
	@scripts/verify.py
