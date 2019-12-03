#include "ft_printf.h"
#include <limits.h>

static int		ft_size(int i)
{
	int j;
	j = 1;
	while (i > 9 || i < 0)
	{
		i = i / 10;
		j++;
	}
	return (j);
}

char			*ft_itoab(long long int  n, short flag)
{
	char	*s;
	int		i;
	int		ss;

	if ((flag & 0b1) == 1)
		n = (char)n;
	if ((flag & 0b10) == 2)
		n = (short)n;
	if ((flag & 0b100) == 4)
		n = (long long int)n;
	if ((flag & 0b1000) == 8)
		n = (long int)n;
	else
		n = (int)n;
	ss = 1;
	i = ft_size(n);
	if (!(s = (char *)malloc(i + 1)))
		return (NULL);
	if (n < 0)
	{
		ss = -1;
		s[0] = '-';
	}
	s[i--] = '\0';
	while (CHECK(n) > 0)
	{
		s[i--] = ((n % 10) * ss) + '0';
		if (n > 9 || n < -9)
			n = n / 10;
	}
	return (s);
}

char	*ft_itob(size_t i, int base, short flag, char c)
{
	char *num;
	char tab[1000];
	int k;
	int l;

	if ((flag & 0b1) == 1)
		i = (unsigned char)i;
	else if ((flag & 0b10) == 2)
		i = (unsigned short)i;
	else if ((flag & 0b100) == 4)
		i = (unsigned long long int)i;
	else if ((flag & 0b1000) == 8)
		i = (unsigned long int)i;
	else
		i = (unsigned int)i;
	k = 0;
	while (i >= base)
	{
		tab[k++] = ((int)(i % base) <= 9 ? '0' : (c - 10)) + (int)(i % base);
		i = i / base;
	}
	tab[k] = ((int)(i % base) <= 9 ? '0' : (c - 10)) + (int)(i % base);
	num = ft_strnew(k + 1);
	l = 0;
	if (num)
	while (k >= 0)
		num[l++] = tab[k--];
	return (num);
}

char	*ints_manager(short flags, va_list ap, char **conv)
{
	size_t		k;
	char		*res;

	if (IS_UNS)
	{
		k = va_arg(ap, size_t);
		if (*conv[0] == 'x')
			res = ft_itob(k, 16, flags, 'a');
		else if (*conv[0] == 'X')
			res = ft_itob(k, 16, flags, 'A');
		else if (*conv[0] == 'o')
			res = ft_itob(k, 8, flags, 'A');
		else if (*conv[0] == 'u')
			res = ft_itob(k, 10, flags, 'A');
	}
	else if (IS_S)
	{
		k = va_arg(ap, long long int);
		res = ft_itoab(k, flags);
	}
	conv[0]++;
	return (res);
}

char	*convs_manager(short flags, va_list ap, char **conv)
{
	char	*res;

	if (IS_CHAR)
	{
		res = ft_strnew(1);
		if (res)
			res[0] = va_arg(ap, int);
	}
	if (IS_STR)
		res = va_arg(ap, char *);
	if (IS_ADD)
		res = ft_strjoin("0x", ft_itob(va_arg(ap, size_t), 16, 4, 'a'));
	conv[0]++;
	return (res);
}

int		flags_check(short *flags, char **fmt)
{
	if (*fmt[0] == '#' && (C_POINT || C_NUM || C_SUM || C_MIN || C_ZERO))
		return (-1);
	if (*fmt[0] == '.' && C_POINT)
		return (-1);
	if (*fmt[0] == '-' && (C_POINT || C_NUM || C_SUM || C_MIN || C_ZERO))
		return (-1);
	if (*fmt[0] == '+' && (C_POINT || C_NUM || C_SUM || C_MIN || C_ZERO))
		return (-1);
	return (0);
}

void	fill_flags(short *flags, char **fmt, t_inf *inf)
{
	while (IS_FLAG)
	{
		if (*fmt[0] == 'h' && *(fmt[0] + 1) == 'h')
		{
			*flags |= HH;
			fmt[0] += 2;
			break;
		}
		else if (*fmt[0] == 'h')
		{
			*flags |= H;
			fmt[0]++;
			break;
		}
		else if (*fmt[0] == 'l' && *(fmt[0] + 1) == 'l')
		{
			*flags |= LL;
			fmt[0] += 2;
			break;
		}	
		else if (*fmt[0] == 'l')
		{
			*flags |= LL;
			fmt[0]++;
			break;
		}
		if (*fmt[0] == 'L')
		{
			*flags |= ML;
			fmt[0]++;
			break;
		}
		if (*fmt[0] == '#')
		{
			fmt[0]++;
			*flags |= HASH;
		}
		else if (*fmt[0] == '-')
		{
			if (ft_isdigit(*(fmt[0] + 1)))
			{
				inf->left = ft_atoi(++fmt[0]);
				while (*fmt[0] && ft_isdigit(*fmt[0]))
					fmt[0]++;
				*flags |= MIN;
			}
			else
				fmt[0]++;
		}
		else if (*fmt[0] == '+')
		{
			if (ft_isdigit(*(fmt[0] + 1)))
			{
				inf->right = ft_atoi(++fmt[0]);
				while (*fmt[0] && ft_isdigit(*fmt[0]))
					fmt[0]++;
				*flags |= SUM;
			}
			else
				fmt[0]++;
		}
		else if (*fmt[0] == '0')
		{
			if (ft_isdigit(*(fmt[0] + 1)))
			{
				*flags |= ZERO;
				inf->left = ft_atoi(++fmt[0]);
				while (*fmt[0] && ft_isdigit(*fmt[0]))
					fmt[0]++;
			}
			else
				fmt[0]++;
		}
		else if (ft_isdigit(*fmt[0]))
		{
			inf->right = ft_atoi(fmt[0]);
			while (*fmt[0] && ft_isdigit(*fmt[0]))
				fmt[0]++;
			*flags |= NUM;
		}
		else if (*fmt[0] == '.')
		{
			inf->right = ft_atoi(fmt[0]);
			while (*fmt[0] && ft_isdigit(*fmt[0]))
				fmt[0]++;
			*flags |= POINT;
		}
		if (flags_check(flags, fmt) < 0)
		{
			*flags = -1;
			break;
		}
	}
}

void	write_chars(char c, size_t lengh)
{

	while (lengh--)
		write(1, &c, 1);
}

int		conversions_managing(va_list ap, char **fmt)
{
	short	flags;
	char	*res;
	t_inf	inf;
	int		pos; // pos

	flags = 0;
	res = NULL;
	fill_flags(&flags, fmt, &inf);
	if (flags == -1)
	{
		printf("ERROR (())\n");
		while (*fmt[0] != '%')
			fmt[0]--;
	}
	//	if (! ! ! !)
	else
	{
		if (IS_INTS)
		{
			res = ints_manager(flags, ap, fmt);
		}
		else if (IS_CONVS)
		{
			res = convs_manager(flags, ap, fmt);
		}
	/*	else if (IS_FLOAT)
		{
			float_manager(flags, ap);
		}
		else if (IS_PERSENT)
		{
			persent_manager(flags, ap);
		}
		*/
		if ((flags & ZERO) == ZERO)
		{
			pos = (int)POS((int)(inf.left - ft_strlen(res)));
			write_chars('0', pos);
			ft_putstr(res);
		}
		if ((flags & SUM) == SUM)
		{
			if (res)
			{
				pos = POS((int)(inf.right - (ft_strlen(res) + ((res[0] == '-') ? 0 : 1))));
				write_chars(' ', pos);
				if (res[0] != '-')
					ft_putchar('+');
				ft_putstr(res);
			}
		}
		if ((flags & MIN) == MIN)
		{
			ft_putstr(res);
			pos = (int)POS((int)(inf.left - ft_strlen(res)));
			write_chars(' ', pos);
		}
		if ((flags & HASH) == HASH)
		{
			if (*fmt[0] == 'o')
				ft_putchar('0');
			else if (*fmt[0] == 'X')
				ft_putstr("0X");
			else if (*fmt[0] == 'x')
				ft_putstr("0x");
		if (*fmt[0] == 'o' || *fmt[0] == 'X' || *fmt[0] == 'x')
			ft_putstr(res);
		}
	}
	return (0);
}

int		ft_printf(char *fmt, ...)
{
	va_list ap, ap2;

	va_start(ap, fmt);
	va_copy(ap2, ap);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			conversions_managing(ap, &fmt);
		}
		if (*fmt)
			ft_putchar(*fmt);
		else
			break;
		fmt++;
	}
	return (0);
}

int main()
{
	size_t k = ULONG_MAX;
	ft_putstr("TR == %-033d\n");
	ft_printf("TR == %-033d\n", 5555);
	printf("\n ********************************\n");
	ft_putstr("TR ==%#-2d0\n");
	ft_printf("TR ==%#-2d0\n", -5555);
	printf("TR ==%#-3d0\n", -5555);
	printf("\n ********************************\n");
	ft_putstr("TR ==%-4d0\n");
	ft_printf("TR ==%-4d0\n", -5);
	printf("TR ==%-4d0\n", -5);
	printf("\n ********************************\n");
	ft_putstr("TR == %#-199-321s\n");
	ft_printf("TR == %#-199-321s\n", "ALLO");
	//	ft_printf("STR=%#10s ADD=%p CHAR=%c INT=%d HEX=%X hex=%x OCT=%o UNS=%u \n", "ALLO", &k, 'A', 777, 777, 777, 777, -777);
	return (0);
}
