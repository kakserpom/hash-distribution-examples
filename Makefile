all: build test
build:
	cd cpp; make; cd -
	cd js; npm i; foobar; cd -
test:

	##### C++ #####
	cpp/dht This
	cpp/dht is
	cpp/dht cool
	##### JS #####
	node js/dht.js This
	node js/dht.js is
	node js/dht.js cool
	##### PHP #####
	php php/dht.php This
	php php/dht.php is
	php php/dht.php cool
