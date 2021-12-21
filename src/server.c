/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:30:19 by dcavalei          #+#    #+#             */
/*   Updated: 2021/12/20 20:35:04 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

t_data	g_data;

int	main(void)
{
	struct sigaction	bit_on;
	struct sigaction	bit_off;

	bit_on.sa_sigaction = &bit_on_handler;
	bit_off.sa_sigaction = &bit_off_handler;
	bit_on.sa_flags = SA_SIGINFO;
	bit_off.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &bit_on, NULL);
	sigaction(SIGUSR2, &bit_off, NULL);
	ft_bzero((void *)g_data.buffer, MAX_CHARS);
	g_data.c = 0;
	g_data.index = 0;
	g_data.client_pid = 0;
	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putstr_fd("\n", 1);
	loop_handler();
}

void	bit_on_handler(int sig, siginfo_t *info, void *ucontext)
{
	unsigned char	bit;

	(void)ucontext;
	(void)sig;
	bit = 0b10000000;
	g_data.c |= bit >> g_data.index;
	g_data.index++;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
}

void	bit_off_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	g_data.index++;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
}

void	loop_handler(void)
{
	int	i;

	i = 0;
	while (1)
	{
		pause();
		if (g_data.index == 8)
		{
			while (g_data.buffer[i] && i < MAX_CHARS)
				i++;
			if (i == MAX_CHARS)
				error_handler(STR_TOO_LONG);
			if (g_data.c == 0)
				null_handler(i);
			g_data.buffer[i] = g_data.c;
			g_data.c = 0;
			g_data.index = 0;
			i = 0;
		}
	}
}

void	null_handler(int i)
{
	ft_putstr_fd(g_data.buffer, 1);
	ft_putchar_fd('\n', 1);
	ft_bzero(g_data.buffer, i);
	kill(g_data.client_pid, SIGUSR1);
	g_data.client_pid = 0;
}
