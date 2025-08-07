
#include "minishell.h"

static void	ft_handle_ctrl_c_heredoc(int sig)
{

	if (sig == SIGINT)
	{
		ft_printf(STDERR_FILENO, "\n");
		close(STDIN_FILENO);
		g_exit_code = 130;
	}
}

void	ft_set_signal_child_heredoc(void)
{
	struct sigaction	sig_child;

	sig_child.sa_handler = ft_handle_ctrl_c_heredoc;
	sigemptyset(&sig_child.sa_mask);
	sig_child.sa_flags = 0;
	sigaction(SIGINT, &sig_child, NULL);
}
