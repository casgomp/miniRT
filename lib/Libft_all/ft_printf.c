/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdella <aabdella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:24:29 by aabdella          #+#    #+#             */
/*   Updated: 2026/02/02 18:24:31 by aabdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_check_specifier(const char *format, va_list args,
				int *count, int *i);

static void	ft_putchar_p(unsigned char c, int *count, int *i);

static void	ft_pointer_check(void *p, int *count, int *i);

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start (args, format);
	while (format[i])
	{
		if (format[i] != '%')
			ft_putstr_p(&format[i], &count, &i, 1);
		if (format[i] == '%' && format[i + 1])
			ft_check_specifier(format, args, &count, &i);
	}
	va_end (args);
	return (count);
}

static void	ft_check_specifier(const char *format, va_list args,
				int *count, int *i)
{
	char	speci;

	speci = format[*i + 1];
	if (speci == 's')
		ft_putstr_p(va_arg (args, char *), count, i, 2);
	if (speci == 'c')
		ft_putchar_p((unsigned char)va_arg (args, int), count, i);
	if (speci == '%')
		ft_putchar_p('%', count, i);
	if (speci == 'd' || speci == 'i')
		ft_putnum_p((long long)va_arg (args, int), count, i, 0);
	if (speci == 'u')
		ft_putnum_p((long long)va_arg (args, unsigned int), count, i, 0);
	if (speci == 'x' || speci == 'X')
		ft_puthex_p((unsigned long)va_arg (args, unsigned int), count, i,
			(unsigned char)format [*i + 1]);
	if (speci == 'p')
		ft_pointer_check(va_arg(args, void *), count, i);
}

static void	ft_putchar_p(unsigned char c, int *count, int *i)
{
	*i += 2;
	*count += 1;
	write (1, &c, 1);
}

static void	ft_pointer_check(void *p, int *count, int *i)
{
	if (p == NULL)
	{
		write (1, "(nil)", 5);
		*count += 5;
		*i += 2;
	}
	else
	{
		write (1, "0x", 2);
		*count += 2;
		ft_puthex_p((unsigned long)p, count, i, (unsigned char) 'x');
	}
}
