/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muerdoga <muerdoga@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:47:06 by muerdoga          #+#    #+#             */
/*   Updated: 2022/08/28 17:07:41 by muerdoga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf/ft_printf.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_signalwrite(int s)
{
	static int	bit = 7;
	static int	set = 0;

	if (s == SIGUSR1)
		s = 1;
	else
		s = 0;
	set = set + (s << bit);
	if (bit == 0)
	{
		ft_printf("%c", set);
		bit = 7;
		set = 0;
	}
	else
		bit--;
}

int	main(void)
{
	ft_printf("PID : ");
	ft_putnbr(getpid());
	ft_printf("\n");
	signal(SIGUSR1, ft_signalwrite);
	signal(SIGUSR2, ft_signalwrite);
	while (1)
		pause();
}
