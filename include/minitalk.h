/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 13:31:21 by dcavalei          #+#    #+#             */
/*   Updated: 2021/12/20 20:40:02 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include <signal.h>
# include <errno.h>

# define MAX_CHARS 4096
# define MAX_BITS_PER_CHAR 8
# define INVALID_INPUT -1
# define KILL_ERROR -2
# define STR_TOO_LONG -3
# define NO_FEEDBACK -4

typedef struct s_data
{
	char			buffer[MAX_CHARS];
	unsigned char	c;
	int				index;
	int				client_pid;
}				t_data;

/*
**	server.c
*/

void	bit_on_handler(int sig, siginfo_t *info, void *ucontext);
void	bit_off_handler(int sig, siginfo_t *info, void *ucontext);
void	null_handler(int i);
void	loop_handler(void);

/*
**	client.c
*/

int		send_char_to_server(unsigned char c, int server_pid);
void	feedback_handler(int sig, siginfo_t *info, void *ucontext);
void	error_handler(int error);

#endif
