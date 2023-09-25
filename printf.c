/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:36:16 by jaehejun          #+#    #+#             */
/*   Updated: 2023/09/25 22:47:23 by jaehejun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int	check_format(char format, va_list ap);
int	ft_putchar(char format);
int	ft_putstr(char *format);
int	ft_putnbr(int number);
int	ft_puthex(unsigned int number);
int	ft_printf(const char *format, ...);

void	leaks()
{
	system("leaks a.out");
}

int	main(void)
{
	int		ft_count;
	int		count;

	atexit(leaks);
	ft_count = ft_printf("Hello, %s%c, %d and %x ,%c%d\n", "world", '!', 2147483647, 2147483647, '-', -2147483648);
	count = printf("Hello, %s%c, %d and %x, %c%d\n", "world", '!', 2147483647, 2147483647, '-', -2147483648);
	ft_printf("%d\n", ft_count);
	printf("%d\n", count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	if (*format != '\0')
		va_start(ap, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			count += check_format(*++format, ap);
			format++;
		}
		else
			count += ft_putchar(*format++);
	}
	va_end(ap);
	return (count);
}

int	check_format(char format, va_list ap)
{
	int	count;

	if (format == 'c')
		count = ft_putchar(va_arg(ap, int));
	else if (format == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (format == 'd')
		count = ft_putnbr(va_arg(ap, int));
	else if (format == 'x')
		count = ft_puthex(va_arg(ap, unsigned int));
	else if (format == '%')
		count = ft_putchar('%');
	else
		return (0);
	return (count);
}

int	ft_putchar(char format)
{
	write(1, &format, 1);
	return (1);
}

int	ft_putstr(char *format)
{
	int	count;

	count = 0;
	while (*format != '\0')
	{
		ft_putchar(*format++);
		count++;
	}
	return (count);
}

int	ft_putnbr(int number)
{
	long long	num;
	static int	count;

	num = (long long)number;
	if (num < 0)
	{
		num *= -1;
		ft_putchar('-');
		count++;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar(num % 10 + '0');
	count++;
	return (count);
}

int	ft_puthex(unsigned int number)
{
	static int		count;
	char			*base_low;

	base_low = "0123456789abcdef";
	if (number >= 16)
		ft_puthex(number / 16);
	ft_putchar(base_low[number % 16]);
	count++;
	return (count);
}
