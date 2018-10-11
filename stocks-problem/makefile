compile:
	@$(CXX) -std=c++14 code/stocks-problem.cpp -o a.out
test_code:
	@./a.out < test/test1.txt
run:
	@make compile && bash run-tests.sh && rm a.out