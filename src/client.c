/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:13:50 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/17 14:26:35 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	struct sigaction	feedback;
	char				*str;
	int					server_pid;

	if (argc != 3)
		error_handler(INVALID_INPUT);
	feedback.sa_sigaction = &feedback_handler;
	feedback.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &feedback, NULL);
	str = argv[2];
	server_pid = ft_atoi(argv[1]);
	while (*str)
	{
		if (!send_char_to_server(*str, server_pid))
			error_handler(KILL_ERROR);
		str++;
	}
	if (!send_char_to_server(0, server_pid))
		error_handler(KILL_ERROR);
	sleep(5);
	error_handler(NO_FEEDBACK);
}

int	send_char_to_server(unsigned char c, int server_pid)
{
	unsigned char	bit;

	bit = 0b10000000;
	while (bit)
	{
		if (bit & c)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (0);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				return (0);
		}
		bit >>= 1;
		usleep(100);
	}
	return (1);
}

void	feedback_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)info;
	(void)ucontext;
	ft_putstr_fd("Message received!\n", 1);
	exit(0);
}
