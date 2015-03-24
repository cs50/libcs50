VERSION=6

all:
	tar -czf library50-c_$(VERSION).orig.tar.gz library50-c-$(VERSION)
	cd library50-c-$(VERSION) && debuild -us -uc

host:
	sudo apt-get install devscripts debhelper
