/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:12:13 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:35:12 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *line, int *nb)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	if (line[i] == '-')
		i++;
	while (line[i] && line[i] >= 48 && line[i] <= 57)
		n = 10 * n + (line[i++] - 48);
	if (i == 0 || (line[0] == '-' && i == 1))
		return (0);
	if (line[0] == '-')
		*nb = -n;
	else
		*nb = n;
	return (i);
}

long	get_t(t_all *all)
{
	struct timeval	buf_time;
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	buf_time.tv_sec = time.tv_sec - all->start_t.tv_sec;
	buf_time.tv_usec = time.tv_usec - all->start_t.tv_usec;
	if (buf_time.tv_usec < 0)
	{
		buf_time.tv_sec--;
		buf_time.tv_usec += 1000000;
	}
	return (buf_time.tv_sec * 1000 + buf_time.tv_usec / 1000);
}

int	my_sleep(t_all *all, long n)
{
	long	time;

	time = get_t(all) + n;
	if (time == n - 1)
		return (0);
	while (get_t(all) < time)
		usleep(100);
	return (1);
}

void	my_free(t_philo **philo)
{
	sem_close(philo[0]->all->fork);
	sem_close(philo[0]->all->print);
}
