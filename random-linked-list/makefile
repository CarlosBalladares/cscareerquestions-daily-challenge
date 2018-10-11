compile:
	@$(CXX) -std=c++14 code/random-linked-list.cpp -o a.out
test_code:
	@./a.out < test/test1.txt
run:
	@make compile && bash run-tests.sh && rm a.out
test_one:
	@make compile && ./a.out < $(file) && rm a.out
compile_debug:
	@clang++ -std=c++14 -g code/random-linked-list.cpp -o a.out

