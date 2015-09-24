PROGRAM := simpletest
CXXFLAGS += -g -Wall -std=c++14
CPPFLAGS += -Iexternal/googletest/googlemock/include \
	    -Iexternal/googletest/googletest/include
LDFLAGS +=
LDLIBS += $(GTESTLIBS) -pthread
GTESTLIBS := external/googletest/googlemock/make/gmock_main.a \
	     external/googletest/googletest/make/gtest_main.a
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(PROGRAM)

$(PROGRAM): $(GTESTLIBS) $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	@rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	@./$(PROGRAM)

# Google Mock/Test
external/googletest/googletest external/googletest/googlemock:
	@git submodule update --init

external/googletest/googlemock/gtest: external/googletest/googlemock
	@ln -s ../googletest external/googletest/googlemock/gtest

external/googletest/googlemock/make/gmock_main.a: external/googletest/googlemock external/googletest/googlemock/gtest
	@CXXFLAGS="-w" make -C external/googletest/googlemock/make gmock_main.a

external/googletest/googletest/make/gtest_main.a: external/googletest/googletest
	@CXXFLAGS="-w" make -C external/googletest/googletest/make gtest_main.a

