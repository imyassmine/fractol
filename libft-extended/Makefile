# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ LAYOUT ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

DEFAULT			= \033[0m
GREEN			= \033[1;32m
CYAN			= \033[1;36m


define ANIMATION_FRAME
				@for frame in ⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏; do \
				printf "$$frame $(1)...\r"; \
				sleep 0.02; \
				done; \
				printf "\n"
endef


# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ VARIABLES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

NAME =			libft.a
CC =			cc
CFLAGS =		-Wall -Wextra -Werror -I include

SRC_DIRS =		libft/src/ get_next_line/src/ ft_printf/src/
OBJ_DIR =		obj/

SRC =			$(foreach d,$(SRC_DIRS),$(wildcard $(d)*.c))
OBJ =			$(SRC:%.c=$(OBJ_DIR)%.o)


# ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ RULES ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

all:			$(NAME)

$(OBJ_DIR)%.o:	%.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(call ANIMATION_FRAME,Building library)
				@ar rcs $(NAME) $(OBJ)
				@printf "$(GREEN)✓$(DEFAULT) Built successfully ($(words $?)/$(words $(SRC)) files recompiled)\n"

clean:
				@rm -rf $(OBJ_DIR)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

help:
				@printf "Usage: make [target]\n"
				@printf "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
				@printf "$(CYAN)all$(DEFAULT)		- Build the library $(NAME)\n"
				@printf "$(CYAN)clean$(DEFAULT)		- Clean up object files\n"
				@printf "$(CYAN)fclean$(DEFAULT)		- Clean up all object files and library\n"
				@printf "$(CYAN)re$(DEFAULT)		- Rebuild the entire library\n"
				@printf "$(CYAN)help$(DEFAULT)		- Show this help message\n"

.PHONY:			all clean fclean re help
