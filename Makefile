CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

all:
	$(CXX) $(CXXFLAGS) main.cpp && ./a.out

fclean: 
	$(RM) a.out

.PHONY: all fclean