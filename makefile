SRC = Gauss.cpp

info:
	clear	
	@echo ========================================================
	@echo You can choose which kind action you need
	@echo type: make launch  -------for make ./lauch exe
	@echo type: make mygprof -------for prof
	@echo type: make mylcov  -------for grof
	@echo type: make clean   -------for clean 
	@echo type: make generate ------for generating A and B matrix
	@echo ========================================================

launch:$(SRC)
	gcc --coverage $(SRC) -g -o launch -lstdc++
	ctags -R .
	./launch
	@gcov $(SRC) -m

mygprof:$(SRC)
	gcc -pg $(SRC) -o launch -lstdc++
	gprof launch gmon.out


mylcov:$(SRC)
	gcc --coverage $(SRC) -o launch -lstdc++
	./launch
	lcov -t "result" -o ex_text.info -c -d .

mygcov:$(SRC)
	genhtml -o rs ex_text.info
	xdg-open ./rs/index.html  #you need xdg-open in your pc
  
generate:
	make -f make_gener clean
	make -f make_gener
	./glaunch	
clean:
	rm -rf launch .gcda .gcdo gmon.out
