
#include "minishell.h"

int	ft_len_table(char **table)
{
	int	l;

	l = 0;
	if (!table || !*(table))
		return (l);
	while (table[l])
		l++;
	return (l);
}
