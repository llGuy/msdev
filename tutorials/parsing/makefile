COUNT_SRC=count_main.cpp
COUNT_FLEXSRC=count.flex
COUNT_OBJS=$(COUNT_SRC:.cpp=.o) $(COUNT_FLEXSRC:.flex=.o)
COUNT_DEPS=$(COUNT_OBJS:.o=.d)

CALC_SRC=calc_main.cpp
CALC_FLEXSRC=calc_tokenize.flex
CALC_BISONSRC=calc_grammar.ypp
CALC_OBJS=$(CALC_SRC:.cpp=.o) $(CALC_FLEXSRC:.flex=.o) $(CALC_BISONSRC:.ypp=.o)
CALC_DEPS=$(CALC_OBJS:.o=.d)

OBJ2OGL_SRC=obj2ogl_main.cpp
OBJ2OGL_FLEXSRC=obj2ogl_tokenize.flex
OBJ2OGL_BISONSRC=obj2ogl_grammar.ypp
OBJ2OGL_OBJS=$(OBJ2OGL_SRC:.cpp=.o) $(OBJ2OGL_FLEXSRC:.flex=.o) $(OBJ2OGL_BISONSRC:.ypp=.o)
OBJ2OGL_DEPS=$(OBJ2OGL_OBJS:.o=.d)

FLEXSRC=$(CALC_FLEXSRC) $(COUNT_FLEXSRC) $(OBJ2OGL_FLEXSRC)
BISONSRC=$(CALC_BISONSRC) $(COUNT_BISONSRC) $(OBJ2OGL_BISONSRC)

DEPS=$(CALC_DEPS) $(COUNT_DEPS) $(OBJ2OGL_DEPS)

INTERMEDIARIES=$(FLEXSRC:.flex=.cpp) $(BISONSRC:.ypp=.cpp) $(BISONSRC:.ypp=.hpp)

CXX=clang++
CFLAGS=-g 
CPPFLAGS=-g -std=c++11
FLEX=flex
FFLAGS=
BISON=bison

%.cpp: %.ypp
	$(BISON) -o $@ -d $< 

%.cpp: %.flex
	flex -o $@ $<

%.d: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -MF $@ -c $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: count calc obj2ogl

count: $(COUNT_OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(COUNT_OBJS)

calc: $(CALC_OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(CALC_OBJS)

obj2ogl: $(OBJ2OGL_OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJ2OGL_OBJS)
.PHONY: clean
clean:
	rm -fr calc count *.o *~ *.d count.dSYM calc.dSYM $(INTERMEDIARIES)


.PHONY: depend
depend: $(DEPS)
	@echo Depend: $(DEPS)

include $(DEPS)
