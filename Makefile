# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 17:33:28 by ael-idri          #+#    #+#              #
#    Updated: 2022/09/07 09:12:44 by zel-hach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	 	=	minishell
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf
define HEADERS
##     ## #### ##    ## ####  ######  ##     ## ######## ##       ##       
###   ###  ##  ###   ##  ##  ##    ## ##     ## ##       ##       ##       
#### ####  ##  ####  ##  ##  ##       ##     ## ##       ##       ##       
## ### ##  ##  ## ## ##  ##   ######  ######### ######   ##       ##       
##     ##  ##  ##  ####  ##        ## ##     ## ##       ##       ##       
##     ##  ##  ##   ###  ##  ##    ## ##     ## ##       ##       ##       
##     ## #### ##    ## ####  ######  ##     ## ######## ######## ######## 
endef
export HEADERS
SRCS	 	=	./lexer/token.c ./lexer/token_tools.c ./lexer/syntax_error.c \
				./lexer/tokens_utils.c ./lexer/join_quote.c					 \
				./lexer/change_dollars.c ./lexer/manage_error.c				 \
				./lexer/heredoc_delimiter.c	./lexer/join_words.c			 \
				./lexer/split_by_spaces.c ./lexer/creat_dollar_tokens.c		 \
				./lexer/ft_creat_quots.c \
				./parser/free_pipe_seq.c   ./parser/get_cmd_suff.c    		 \
				./parser/get_command.c     ./parser/get_pipe_seq.c   		 \
				./parser/get_redirection.c ./parser/parser.c				 \
				./parser/read_pipe_seq.c									 \
				./execution/bultins/builtin_cd.c ./execution/bultins/utile_cd.c ./execution/bultins/builtin_echo.c ./execution/bultins/builtin_env.c \
				./execution/bultins/builtin_exit.c ./execution/bultins/builtin_export.c ./execution/bultins/utils_export.c \
				./execution/bultins/builtin_pwd.c ./execution/bultins/builtin_unset.c  ./execution/bultins/add_export.c \
				./execution/non_bultins/main_exec.c ./execution/non_bultins/utils_non_bultins.c \
				./execution/redirection/herdoc.c \
				./execution/redirection/redir_herdoc.c \
				./execution/free.c \
				./signals/signal_handler.c ./execution/pipe/ft_pipe.c main.c												 
OBJS		=	$(SRCS:.c=.o)
LIBFT		=	./libft/libft.a
PATH_LIBFT	=	./libft/
HEADER		=	minishell.h

all			: $(NAME)

${LIBFT}	:
				@make -C ${PATH_LIBFT}

$(NAME)		:print_header $(OBJS) ${LIBFT} 
				@${CC} ${FLAGS}  -lreadline  -L /Users/${USER}/.brew/opt/readline/lib \
				 ${OBJS} -o $(NAME) $(LIBFT)

print_header:
	@echo "\033[0;32m $$HEADERS \033[0;32m"
%.o			:	%.c $(HEADER)
				@$(CC) ${FLAGS} -c -I /Users/${USER}/.brew/opt/readline/include $< -o $@
				@echo "\033[1;35m  $@ is created ✅  \033[1;37m"
    
clean		:
				@$(RM) $(OBJS)
				@make clean -C ${PATH_LIBFT}

fclean		:	clean
				@$(RM) $(NAME)
				@make fclean -C ${PATH_LIBFT}
				@echo "\033[1;35m  $(NAME) is deleted ✅  \033[0;37m"

re			:	fclean all

.PHONY		:	all clean fclean re