NAME = philo
CC = clang
CFLAGS = -Werror -Wextra -Wall -pthread
SFLAGS = -fsanitize=address -g3
RM = rm -rf

FILES = srcs/main \
		srcs/philo \
		srcs/utils \
		srcs/routine \
		utils/ft_atoi 

SRC = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

.c.o: $(FILES)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(SRC)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\e[32mCompiled into "philo" and ready to be launched 🤠\e[0m\n"

s:	$(OBJS) $(SRC)
	@$(CC) $(CFLAGS) $(SFLAGS) $(OBJS) -o $(NAME)
	@printf "\e[32mCompiled into "philo" with fsanitize 💉\e[0m\n"

clean: 
	@$(RM) $(OBJS) *.dSYM
	@printf "\e[33mAll .o's have been 💥 obliterated 💥\e[0m\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "\e[33m+ratio💯 +cringe😬 +$(NAME) deleted🗑️\e[0m\n"


re: fclean all

.PHONY: all s clean fclean re
