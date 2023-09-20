CXX=g++ -std=c++17
FLAGS=-Wall -Wextra -Werror

LIBS=-lgtest -lgtest_main
OPEN=xdg-open

ifeq ($(shell uname -s), Darwin)
	OPEN=open
else
	LIBS+=-lm
	OPEN=xdg-open
endif

all: test

test: clean
	$(CXX) $(FLAG) s21_tests.cc $(LIBS) -o test
	./test

gcov_report: clean
	$(CXX) $(FLAG) --coverage s21_tests.cc $(LIBS) -o test
	./test
	@gcovr -r . --html --html-details -o report.html
	@$(OPEN) report.html 2>/dev/null

style:
	clang-format -n --style=Google *.cc *.h containers/*.h tests/*.cc

clean:
	rm -rf *.o *.gcda *gcno *.html *.css test