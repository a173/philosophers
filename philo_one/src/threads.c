/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:56 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:34:07 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print(t_all *all, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (pthread_mutex_lock(all->print) != 0)
		return (0);
	printf("%ld %d %s\n", time, id, str);
	if (pthread_mutex_unlock(all->print) != 0)
		return (0);
	return (1);
}

static int	count_i(t_philo *ph, int flag, int n)
{
	if (ph->all->count_eat)
	{
		if (pthread_mutex_lock(ph->all->print))
			return (0);
		if (flag)
		{
			if (ph->i == ph->all->count_eat)
			{
				ph->status++;
				n--;
				ph->all->end++;
			}
		}
		else
			if (ph->all->end >= ph->all->count_philo)
				n--;
		if (pthread_mutex_unlock(ph->all->print))
			return (0);
	}
	return (n);
}

static void	*thread(void *buf)
{
	t_philo			*ph;	

	ph = buf;
	if (pthread_detach(ph->t))
		pthread_exit(0);
	while (1)
	{
		if (pthread_mutex_lock(ph->left) || pthread_mutex_lock(ph->right))
			pthread_exit(0);
		ph->t_eat = get_t(ph->all);
		if (ph->t_eat == -1)
			pthread_exit(0);
		if (!print(ph->all, "has taken a fork", ph->t_eat, ph->id) || \
			!print(ph->all, "is eating", ph->t_eat, ph->id))
			pthread_exit(0);
		if (!my_sleep(ph->all, ph->all->t_eat) || \
			pthread_mutex_unlock(ph->right) || pthread_mutex_unlock(ph->left))
			pthread_exit(0);
		if ((++ph->i && !count_i(ph, 1, 1)) || !print(ph->all, "is sleeping", \
			get_t(ph->all), ph->id) || !my_sleep(ph->all, ph->all->t_sleep) \
			|| !print(ph->all, "is thinking", get_t(ph->all), ph->id))
			pthread_exit(0);
	}
}

static void	*cracken(void *buf)
{
	t_philo	**p;
	int		i;
	long	buf_time;

	p = buf;
	while (1)
	{
		i = -1;
		while (p[++i])
		{
			buf_time = get_t(p[i]->all) - (p[i]->t_eat + p[i]->all->t_dead);
			if (!count_i(p[i], 0, 1) || (!p[i]->status && buf_time > 0))
			{
				if (count_i(p[i], 0, 1))
					print(p[i]->all, "is dead", get_t(p[i]->all), p[i]->id);
				if (pthread_mutex_unlock(p[i]->all->print))
					print(p[i]->all, "error", get_t(p[i]->all), 0000000000);
				pthread_exit(0);
			}
		}
	}
}

int	live(t_philo **philo, int i)
{
	if (pthread_create(&philo[0]->all->t, NULL, cracken, (void *)philo))
		return (0);
	while (philo[++i] != NULL)
	{
		if (pthread_create(&philo[i]->t, NULL, thread, (void *)philo[i]))
			return (0);
		usleep(10);
	}
	if (pthread_join(philo[0]->all->t, NULL))
		return (0);
	return (1);
}
