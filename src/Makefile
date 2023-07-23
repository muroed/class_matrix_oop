COMPILER:=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
COMPILER+=-DCMAKE_CXX_COMPILER=/usr/bin/g++
endif
ifeq ($(UNAME_S),Darwin)
UNAME_M := $(shell uname -m)
	ifeq ($(UNAME_M),x86_64)
COMPILER+=-DCMAKE_CXX_COMPILER=/usr/local/bin/g++
	endif
	ifeq ($(UNAME_M), arm64)
COMPILER+=-DCMAKE_CXX_COMPILER=/Library/Developer/CommandLineTools/usr/bin/g++
	endif
endif

all: nd_matrix_oop.a

nd_matrix_oop.a:
	cmake -B./build -S. $(COMPILER) && cd build && make nd_matrix_oop_source
	cp -f ./build/source/nd_matrix_oop.a ./

test:
	cmake -B./build -S. $(COMPILER) -DCMAKE_BUILD_TYPE=Build
	cd build && make && make matrix_test
	cp -f ./build/tests/matrix_test ./
	./matrix_test


gcov_report:
	cmake -DCMAKE_BUILD_TYPE=Debug $(COMPILER) -B./build 
	cd build && make && make nd_matrix_oop_coverage
	open build/coverage/index.html

clean:
	rm -f ./nd_matrix_oop.a ./matrix_test
	rm -rf build/
	
style:
	cp ../materials/linters/.clang-format ./
	clang-format -n source/*.cc tests/*.cc
	rm -rf .clang-format

leaks: test
	leaks -atExit -- ./matrix_test

test_linux: 
	cmake -B./build -S. -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_BUILD_TYPE=Build
	cd build && make && make matrix_test
	cp -f ./build/tests/matrix_test ./
	./matrix_test

valgrind_docker: clean
	docker build -t nazeebo/valgrind:latest .
	docker run --name nazeebo_valgrind -d nazeebo/valgrind:latest 
	docker logs nazeebo_valgrind
	docker rm nazeebo_valgrind
	docker rmi -f nazeebo/valgrind:latest

valgrind:
	valgrind --tool=memcheck --leak-check=yes --log-file=val.txt ./build/tests/matrix_test
