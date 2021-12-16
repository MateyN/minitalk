#include "minitalk.h"
#include "libft/libft.h"

void	handler(int sig, siginfo_t *info, void *empty)

{
	static int	value = 0;
	static int	bit = 0;

	(void)info;
	(void)empty;
	if (sig == SIGUSR1)
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
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	if ((sigaction(SIGUSR1, &sa, 0)) < 0)
		write(1, "Error\n", 6);
	if ((sigaction(SIGUSR2, &sa, 0)) < 0)
		write(1, "Error\n", 6);
	while (1)
		pause();
	return (0);
}
