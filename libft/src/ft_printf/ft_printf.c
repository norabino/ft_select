/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:42:04 by norabino          #+#    #+#             */
/*   Updated: 2026/10/16 12:07:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_isconv(char c)
{
	int		i;
	char	*charset;

	i = 0;
	charset = "cspiudxX%";
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_conversions(va_list ap, const char *format, int	*i, int *len)
{
	if (format[*i + 1] && format[*i + 1] == 'c')
		*len += ft_print_c((char)va_arg(ap, int));
	if (format[*i + 1] && format[*i + 1] == 's')
		*len += ft_print_s((char *)va_arg(ap, char *));
	if (format[*i + 1] && format[*i + 1] == 'p')
		*len += ft_print_p((void *)va_arg(ap, void *));
	if (format[*i + 1] && format[*i + 1] == 'i')
		*len += ft_print_d((int)va_arg(ap, int));
	if (format[*i + 1] && format[*i + 1] == 'u')
		*len += ft_print_u((unsigned int)va_arg(ap, unsigned int));
	if (format[*i + 1] && format[*i + 1] == 'd')
		*len += ft_print_d((long)va_arg(ap, long));
	if (format[*i + 1] && format[*i + 1] == 'x')
		*len += ft_print_x((unsigned long long)va_arg(ap, unsigned long long));
	if (format[*i + 1] && format[*i + 1] == 'X')
		*len += ft_print_bx((unsigned long long)va_arg(ap, unsigned long long));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	va_start(ap, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			len += ft_print_c('%');
			i += 2;
			continue ;
		}
		if (format[i] == '%' && ft_isconv(format[i + 1]))
		{
			ft_conversions(ap, format, &i, &len);
			i += 2;
			continue ;
		}
		len += ft_print_c(format[i]);
		i++;
	}
	return (len);
}
