CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

all:
	$(CXX) $(CXXFLAGS) main.cpp && ./a.out

3: 
	$(CXX) $(CXXFLAGS) main_map.cpp && ./a.out	

fclean: 
	$(RM) a.out

.PHONY: all fclean 3