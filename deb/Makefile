VERSION=6

all:
	mv library50-c-$(VERSION)/debian .
	tar -czf library50-c_$(VERSION).orig.tar.gz library50-c-$(VERSION)
	mv debian library50-c-$(VERSION)
	cd library50-c-$(VERSION) && debuild -us -uc
