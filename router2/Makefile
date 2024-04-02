SUBDIRS := port_scan
SUBDIRS += filecut
SUBDIRS += dhcpdump
SUBDIRS += wireless_configure
SUBDIRS += dump_log
SUBDIRS += router
SUBDIRS += d2_client
SUBDIRS += jeff_utf16toAscii

.PHONY: $(SUBDIRS)
	
all:
	for i in ${SUBDIRS}; do \
		(cd $$i; make) || exit 1; \
	done
clean:
	for i in $(SUBDIRS); do \
		(cd $$i; make clean) || exit 1;\
	done
