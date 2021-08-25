/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 06:29:36 by bmoulin           #+#    #+#             */
/*   Updated: 2021/07/30 06:29:40 by bmoulin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

void	use_signal(int sig, siginfo_t *info)
{
	static int	nb = 0;
	static char	c = 0;
	static int	savepid = 0;

	if (!savepid || savepid != info->si_pid)
		savepid = info->si_pid;
	if (sig == SIGUSR1)
		c |= (1 << nb);
	if (sig == SIGUSR2)
		c |= (0 << nb);
	if (nb == 7)
	{
		if (c)
			printf("%c", c);
		if (!c)
			printf("\n");
		nb = 0;
		c = 0;
	}
	else
		nb = nb + 1;
	if (kill(savepid, SIGUSR1) == -1)
		exit(1);
}

int	main(void)
{
	int					pid;
	struct sigaction	action;

	pid = getpid();
	if (pid < 0)
	{
		printf("Error, pid not generated\n");
		exit(1);
	}
	printf("PID %d\n", pid);
	action.sa_sigaction = (void *) use_signal;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
}
