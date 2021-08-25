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

void	send_bit(char c, int bit_nb, int pid)
{
	if ((c >> bit_nb & 1))
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(1);
	}
	if (!(c >> bit_nb & 1))
	{
		if (kill(pid, SIGUSR2) == -1)
			exit(1);
	}
}

void	send_str(char *s, int pid)
{
	static int	i = 0;
	static char	*str = NULL;
	static int	savepid = 0;
	static int	bit_nb = 0;

	if (s)
	{
		str = s;
		savepid = pid;
		if (str && str[i])
			send_bit(str[i], bit_nb++, savepid);
		return ;
	}
	if (str && str[i])
	{
		send_bit(str[i], bit_nb++, savepid);
		if (bit_nb >= 8)
			if (++i)
				bit_nb = 0;
		return ;
	}
	if (str && !str[i] && bit_nb < 8)
		send_bit(0, bit_nb++, savepid);
	if (str && !str[i] && bit_nb >= 8)
		exit(0);
}

void	use_signal(int sig)
{
	static int	i = 0;

	(void)sig;
	send_str(NULL, 0);
	i++;
	usleep(27);
	if (i >= 8 * 2000)
		usleep(50);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	action;

	if (argc != 3)
	{
		printf("Error, bad number of arguments.\n");
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 0)
	{
		printf("PID Error, please enter a valid PID.\n");
		exit (1);
	}
	action.sa_sigaction = (void *) use_signal;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	send_str(argv[2], pid);
	while (1)
		pause();
}
