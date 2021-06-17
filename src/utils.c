/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:32:45 by dcavalei          #+#    #+#             */
/*   Updated: 2021/06/16 15:52:25 by dcavalei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_handler(int error)
{
	ft_putstr_fd("Error!\n", 2);
	if (error == INVALID_INPUT)
		ft_putstr_fd("Invalid input! Try: ./client <pid> <message>\n", 2);
	else if (error == KILL_ERROR)
	{
		ft_putstr_fd("errno code: ", 2);
		ft_putnbr_fd(errno, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error == STR_TOO_LONG)
		ft_putstr_fd("Message too long!\n", 2);
	else if (error == NO_FEEDBACK)
		ft_putstr_fd("No feedback from server!\n", 2);
	else
		ft_putstr_fd("Unknown!\n", 2);
	exit(1);
}
