COUNT_SRC=count_main.cpp
COUNT_FLEXSRC=count.flex
COUNT_OBJS=$(COUNT_SRC:.cpp=.o) $(COUNT_FLEXSRC:.flex=.o)
COUNT_DEPS=$(COUNT_OBJS:.o=.d)

CALC_SRC=calc_main.cpp
CALC_FLEXSRC=calc_tokenize.flex
CALC_BISONSRC=calc_grammar.ypp
CALC_OBJS=$(CALC_SRC:.cpp=.o) $(CALC_FLEXSRC:.flex=.o) $(CALC_BISONSRC:.ypp=.o)
CALC_DEPS=$(CALC_OBJS:.o=.d)

DEPS=$(CALC_DEPS) $(COUNT_DEPS)

CXX=clang++
CFLAGS=-g
CPPFLAGS=-g
FLEX=flex
FFLAGS=
BISON=bison

%.cpp: %.ypp
	$(BISON) -o $@ -d $< 

%.cpp: %.flex
	flex -o $@ $<

%.d: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -MF $@ -c $^

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

all: count calc

count: $(COUNT_OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(COUNT_OBJS)

calc: $(CALC_OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(CALC_OBJS)

clean:
	rm -fr calc count *.o *~ *.d count.dSYM calc.dSYM

depend: $(DEPS)
	@echo Depend: $(DEPS)

include $(DEPS)
