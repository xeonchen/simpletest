PROGRAM := simpletest
CXXFLAGS += -Wall -std=c++17
CPPFLAGS += -Iexternal/googletest/googlemock/include \
	    -Iexternal/googletest/googletest/include
LDFLAGS += -Lexternal/obj/lib
LDLIBS += -lgmock -lgtest -pthread
GTESTLIBS := external/obj/lib/libgmock.a \
	     external/obj/lib/libgtest.a
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(PROGRAM)

$(PROGRAM): $(GTESTLIBS) $(OBJS)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

clean:
	@rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	@./$(PROGRAM)

# Google Mock/Test
external/googletest/googletest external/googletest/googlemock:
	@git submodule update --init

external/obj: external/googletest/googletest external/googletest/googlemock
	@cmake -S external/googletest -B $@

external/obj/lib/libgmock.a external/obj/lib/libgtest.a: external/obj
	@make -C $^

