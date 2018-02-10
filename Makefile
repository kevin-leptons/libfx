config:
	sudo apt-get install sphinx-common cmake
doc-build:
	sphinx-build -b text doc dest/doc/text
	sphinx-build -b html doc dest/doc/html
doc-clear:
	rm -rf dest/doc
doc-open:
	xdg-open dest/doc/html/index.html
src-build:
	mkdir -vp dest
	cd dest; cmake -DCMAKE_BUILD_TYPE="Debug" ..;  make
src-build-release:
	mkdir -vp dest
	cd dest; cmake -DCMAKE_BUILD_TYPE="Release" ..; make
src-clear:
	rm -rf dest
src-test:
	./dest/bin/run_test
build: doc-build src-build
test: src-test
