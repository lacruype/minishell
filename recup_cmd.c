#include "minishell.h"

void	pop_word(char *word, int amount)
{
	while (*(word + amount))
	{
		*word = *(word + amount);
		word++;
	}
	*word = 0;
}

int	count_args(t_node *args)
{
	if (args)
		return (count_args(args->left) + 1);
	else
		return (0);
}

void	fill_args(t_node *args, char **list, int level)
{
	//printf("content is %s\n", args->content);
	if (args)
		fill_args(args->left, list, level + 1);
	if (args && args->content)
		list[level] = args->content;
}

char **generate_arguments(t_node *args)
{
	char **arg_list;

	if (!(arg_list = malloc(sizeof(char*) * (count_args(args) + 1))))
		return (0);
	arg_list[count_args(args)] = 0;
	fill_args(args, arg_list, 0);
	return (arg_list);
}

void handle_d_supp_redir(t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (perror("open()"));

	if (node->left)
	{
		close(fd);
		return (handle_redir(node->left));
	}
	dup2(fd, STDOUT_FILENO);
}

void handle_supp_redir(t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		return (perror("open()"));

	if (node->left)
	{
		close(fd);
		return (handle_redir(node->left));
	}
	dup2(fd, STDOUT_FILENO);
}

void handle_inf_redir(t_node *node)
{
	int fd;

	if ((fd = open(node->content, O_RDONLY)) == -1)
	{
		ft_printf("minishell: %s: %s", strerror(errno), node->content);
		return ;
	}
	if (node->left)
	{
		close(fd);
		return (handle_redir(node->left));
	}
	dup2(fd, STDIN_FILENO);
}

void handle_redir(t_node *node)
{
	if (node->type == e_t_supp)
		handle_supp_redir(node);
	else if (node->type == e_t_inf)
		handle_inf_redir(node);
	else if (node->type == e_t_d_supp)
		handle_d_supp_redir(node);
}

void	execute_command(t_node *cmd_node, t_lexer *lex)
{
	char	**args;
	char	*ex_name;

	if(cmd_node->right)
		handle_redir(cmd_node->right);
	if (starts_with(cmd_node->content, "./"))
	{
		if (!(args = generate_arguments(cmd_node)))
			return ; //malloc fail
		if (!(ex_name = ft_strdup(cmd_node->content)))
			return ;
		pop_word(ex_name, 2);
	}
	else
	{
		if (!(args = generate_arguments(cmd_node)))
			return ; //malloc fail
		if (!(ex_name = get_command_path(get_var(lex->env_list, "PATH")->value, cmd_node->content)))
			return ;
	}
	execve(ex_name, args, lex->envac);
}

void	execute_pipe(t_node *tree, t_lexer *lex, int out_fd)
{
    int status;
	int pfd[2];
    int pid_left, pid_right;

    if (pipe(pfd) == -1) // create pipe
    {
        perror("pipe");
        exit(1);
    }
	if ((pid_right = fork()) == -1) //create right fork child
	{
    	perror("fork");
    	exit(1);
	}
    if (pid_right == 0)		// executes if in right child
	{
		if (out_fd != STDOUT_FILENO)
			dup2(out_fd, STDOUT_FILENO); //bind output to out_fd which would be input of superior level or 1 if level 0
        dup2(pfd[0], STDIN_FILENO); // bind input to end of pipe
    	close(pfd[1]);				// ignore pipe pipe entry
    	return (execute_command(tree->right, lex)); //right child end
   	}
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (tree->left->type == e_t_cmd_name) // if left side is cmd, we are in deepest level
	{
    	if ((pid_left = fork()) < 0) //fork left child
    	{
    	    perror("fork");
    	    exit(1);
    	}
   		if (pid_left == 0) // executes if in left child
    	{
    	    dup2(pfd[1], STDOUT_FILENO);	// bind output to pipe entry
			close(pfd[0]);					// close end of pipe as left child sends output to right child
    	    return (execute_command(tree->left, lex)); // left child end
    	}

	$(PATH)main.c \
		$(PATH)ft_echo.c \
		$(PATH)ft_utils.c \
		$(PATH)ft_utils02.c \
		$(PATH)ft_pwd.c \
		$(PATH)ft_envv.c \
		$(PATH)ft_error.c \
		$(PATH)ft_parsing01.c \
		$(PATH)ft_env.c \
		$(PATH)ft_split_semicolon.c \
		$(PATH)ft_path.c \
		$(PATH)ft_escape_char.c \
		$(PATH)ft_split_cmd.c \

		// we are in parent process, child will never reach this line,  ENF OF FLOW 
		close(pfd[0]);
		close(pfd[1]);
		waitpid(pid_left, &status, 0);
		waitpid(pid_right, &status, 0);
	}
	else // left is a pipe
	{
		close(pfd[0]); // close end of pipe data lost
		execute_pipe(tree->left, lex, pfd[1]); // recursion
		waitpid(pid_right, &status, 0);
	}
}

void	execute_tree(t_lexer *lex, t_node *node)
{
	pid_t	new_id;
	int		a;

	if (!node)
		return ;
	if (node->type == e_t_semi_colon)
	{
		execute_tree(lex, node->left);
		execute_tree(lex, node->right);
	}
	else if (node->type == e_t_cmd_name)
	{
		if((new_id = fork()) == 0)
			execute_command(node, lex);
		else
			waitpid(new_id, &a, 0);	
	}
	if (node->type == e_t_pipe)
		return (execute_pipe(node, lex, STDOUT_FILENO));
}