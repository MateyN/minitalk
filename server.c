/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                             	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <mnikolov@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:13:45 by mnikolov          #+#    #+#             */
/*   Updated: 2021/12/16 14:06:07 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"
/*
** This function is the handler for messaging signals (SIGUSR1 = 0,
** SIGUSR2 = 1). It will keep tracking of the received bits until it has
** a full character, printing it and resetting.
*/
void	handler(int signum, siginfo_t *info, void *empty)

{
	static int	value = 0;
	static int	bit = 0;

	(void)info;
	(void)empty;
	if (signum == SIGUSR1)
		value += 1 << bit;
	bit += 1;
	if (bit == 8)
	{
		ft_putchar_fd(value, 1);
		bit = 0;
		value = 0;
	}
}

int	main(void)

{
	struct sigaction	sa;

	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);		// getpid() to output to the user its PID, and 
	write(1, "\n", 1);				// later will be used to compile client.
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	if ((sigaction(SIGUSR1, &sa, 0)) < 0)
		write(1, "Error\n", 6);
	if ((sigaction(SIGUSR2, &sa, 0)) < 0)
		write(1, "Error\n", 6);
	while (1)						// The function then enters an infinite pause() loop, 
		pause();					// waiting for signals from client.
	return (0);
}
