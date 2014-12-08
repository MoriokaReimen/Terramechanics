CXX = g++
CXX_FLAG = -std=c++11 -Iinclude
RELEASE_FLAGS = -Ofast -march=native
DEBUG_FLAGS = -g

#Release build
build/bevameter-release.o: src/bevameter.cpp include/bevameter.hpp
	$(CXX) $(CXX_FLAG) $(RELEASE_FLAGS) -c src/bevameter.cpp -o $@

#Dbug build
build/bevameter-debug.o: src/bevameter.cpp include/bevameter.hpp
	$(CXX) $(CXX_FLAG) $(DEBUG_FLAGS) -c src/bevameter.cpp -o $@

clean:
	@rm build/*.o
