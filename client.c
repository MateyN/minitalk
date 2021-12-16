/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                             	        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnikolov <mnikolov@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:13:45 by mnikolov          #+#    #+#             */
/*   Updated: 2021/12/16 14:06:07 by mnikolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minitalk.h"

void	send_char_by_bit(int pid, char *byte)

{
	static int	i;
	static int	j;

	i = 0;
	j = 0;
	while (j < 8)
	{
		if ((byte[i] >> j) & 1)						// Iterate through the string shifting the bits by one to the right.
		{
			if (kill(pid, SIGUSR1) == -1)
				write(1, "No server found\n", 16);	// Error if wrong PID is entered for SIGUSR1.
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)			// Error if wrong PID is entered for SIGUSR2.
				write(1, "No server found\n", 16);
		}
		j++;
		usleep(100);
	}
}

static void	acknowledgment(int sig)					// Confirm every signal received by sending a signal to the client (ACK signal).

{
	static int	received = 0;

	if (sig == SIGUSR1)
		++received;
	else
	{
		ft_putnbr_fd(received, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

void	handler(int pid, char *str)
{
	while (*str)
	{
		send_char_by_bit(pid, str);					// Sending the string
		str++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "Invalid arguments\n", 18);		// If the arguments are less than 3 display error.
		return (1);
	}
	ft_putstr_fd("Message received!\n", 1);			// Acknowledge sent.
	signal(SIGUSR1, acknowledgment);
	signal(SIGUSR2, acknowledgment);
	handler((ft_atoi(argv[1])), argv[2]);
	return (0);
}
