/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muerdoga <muerdoga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:47:14 by muerdoga          #+#    #+#             */
/*   Updated: 2022/08/28 17:06:35 by muerdoga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(char *str)
{
	int	i;

	i = 0;
	while (*str)
		i = (i * 10) + (*str++ - '0');
	return (i);
}

void	ft_signalsend(int pid, char *str)
{
	int				i;
	unsigned char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if ((c >> i) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(37);
		}
	}
}

int	main(int ac, char *av[])
{
	if (ac != 3)
	{
		ft_printf("Hatalı argüman girdiniz !");
		return (0);
	}
	ft_signalsend(ft_atoi(av[1]), av[2]);
}
