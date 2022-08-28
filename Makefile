# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberneli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 14:59:12 by aberneli          #+#    #+#              #
#    Updated: 2022/03/26 10:19:18 by aberneli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

CC := gcc
RL_INC := -I$(HOME)/.brew/opt/readline/include
INCLUDE_FLAGS := -I. -Iexec -Iutils -Ienv -Ilexer -Ibuiltin $(RL_INC)
CFLAGS := -Wall -Wextra -Werror $(INCLUDE_FLAGS) -fno-builtin

HEADER := env/env.h utils/utils.h lexer/lexer.h exec/exec.h \
	builtin/builtin.h utils/ft_printf.h ms_signal.h

SRC_EXEC_FILES := exec.c exec_process.c exec_utils.c exec_execute.c
	
SRC_LEXER_FILES := lexer.c cmd.c io.c redir.c token.c pipes.c heredoc.c

SRC_ENV_FILES := env_init.c env_export.c env_display.c env_unset.c env_split.c

SRC_UTILS_FILES := utils_len.c utils_dup.c utils_join.c utils_cmp.c \
	utils_valid.c utils_mem.c utils_chr.c utils_write.c utils_split.c \
	utils_atoi.c utils_str.c utils_str_expand.c utils_qsplit.c utils_itoa.c \
	ft_converter.c ft_convsint.c ft_convstr.c ft_convuint.c ft_convxint.c \
	ft_getters.c ft_tools.c ft_printf.c
	
SRC_BUILTIN_FILES := builtin_cd.c builtin_echo.c builtin_exit.c \
	builtin_utils.c builtin_env.c builtin_pwd.c

SRC_EXEC	:= $(addprefix exec/, $(SRC_EXEC_FILES))
SRC_LEXER	:= $(addprefix lexer/, $(SRC_LEXER_FILES))
SRC_ENV		:= $(addprefix env/, $(SRC_ENV_FILES))
SRC_UTILS	:= $(addprefix utils/, $(SRC_UTILS_FILES))
SRC_BUILTIN	:= $(addprefix builtin/, $(SRC_BUILTIN_FILES))

SRC := $(SRC_ENV) $(SRC_UTILS) $(SRC_LEXER) $(SRC_EXEC) $(SRC_BUILTIN) \
	main.c signal.c
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(HOME)/.brew/opt/readline/lib -lreadline

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
