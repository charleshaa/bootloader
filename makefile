all:
	cd kernel && $(MAKE) run
clean:
	cd kernel && $(MAKE) clean