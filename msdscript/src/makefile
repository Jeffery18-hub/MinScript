# this is makefile for expression classes

SRCS = main.cpp expr.cpp parse.cpp cmdline.cpp exec.cpp test_msdscript.cpp val.cpp Env.cpp
OBJS = main.o expr.o parse.o cmdline.o val.o Env.o
OBJS1 = exec.o test_msdscript.o
CXXFLAGS = --std=c++14


msdscript: $(OBJS)
	c++ $(CXXFLAGS) $(OBJS) -o $@

#test_msdscript: $(OBJS1)
#	c++ $(CXXFLAGS) $(OBJS1) -o $@

main.o: main.cpp

expr.o: expr.cpp

parse.o: parse.cpp

cmdline.o: cmdline.cpp

exec.o: exec.cpp

val.o: val.cpp

Env.o: Env.cpp

#test_msdscript.o: test_msdscript.cpp

.PHONY: clean

clean:
	rm msdscript *.o

#.PHONY: doc

#doc:
#	cd documentation && doxygen && cd html && open index.html
#
#.PHONY: getPDF
#
#getPDF:
#	cd ~/cs6015/expression/documentation/latex && pdflatex index.tex



