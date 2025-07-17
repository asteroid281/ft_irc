NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR = src
INCDIR = inc
OBJDIR = obj

SOURCES = main.cpp \
		  Server.cpp \
		  Client.cpp \
		  Channel.cpp \
		  Commands.cpp \
		  Utils.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
HEADERS = $(INCDIR)/Server.hpp \
		  $(INCDIR)/Client.hpp \
		  $(INCDIR)/Channel.hpp \
		  $(INCDIR)/Commands.hpp \
		  $(INCDIR)/Utils.hpp

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM)r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
