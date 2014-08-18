# only for cleaning :-)

SUBDIRS = 

.PHONY: all
all: 
	@echo Cheers

.PHONY: clean
clean:
	rm -f *~ *.o *.bak *-bak
	for dir in $(SUBDIRS); do (cd $$dir && $(MAKE) $@); done	


