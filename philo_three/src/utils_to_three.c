/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_to_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 17:13:04 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:24:56 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = -1;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	while (++i < n && (s1[i] || s2[i]))
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	return (0);
}

int	count_i(t_philo *ph)
{
	int	n;

	n = 1;
	if (ph->all->count_eat)
	{
		if (sem_wait(ph->all->print))
			return (0);
		if (ph->i == ph->all->count_eat)
		{
			sem_post(ph->status);
			n--;
		}
		if (sem_post(ph->all->print))
			return (0);
	}
	return (n);
}

static char	*ft_create_array(unsigned int j, int min, unsigned int new)
{
	char			*buf;
	unsigned int	i;

	i = 0;
	buf = malloc(sizeof(char) * (j + 1));
	if (buf)
	{
		buf[j] = 0;
		while (j != 0)
		{
			buf[j - 1] = new % 10 + 48;
			new /= 10;
			j--;
		}
		if (min)
			buf[0] = '-';
	}
	return (buf);
}

char	*ft_itoa(int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	new;
	unsigned int	min;

	if (n == 0)
		return (NULL);
	j = 0;
	min = 0;
	if (n < 0)
	{
		min = 1;
		new = -(unsigned int)n;
		j++;
	}
	else
		new = (unsigned int)n;
	i = new;
	while (i != 0)
	{
		i /= 10;
		j++;
	}
	return (ft_create_array(j, min, new));
}

int	fill_all(char **argv, t_all *all, int i, int j)
{
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (0);
	}
	ft_atoi(argv[0], &all->count_philo);
	ft_atoi(argv[1], &all->t_dead);
	ft_atoi(argv[2], &all->t_eat);
	ft_atoi(argv[3], &all->t_sleep);
	if (gettimeofday(&all->start_t, NULL) == -1)
		return (0);
	all->end = 0;
	if (argv[4])
		ft_atoi(argv[4], &all->count_eat);
	else
		all->count_eat = 0;
	if (all->count_philo < 2 || all->t_dead < 1 || \
		all->t_eat < 1 || all->t_sleep < 1 || all->count_eat < 0)
		return (0);
	return (1);
}
