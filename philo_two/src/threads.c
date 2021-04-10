/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:56 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:25:26 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print(t_all *all, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (sem_wait(all->print) != 0)
		return (0);
	printf("%ld %d %s\n", time, id, str);
	if (sem_post(all->print) != 0)
		return (0);
	return (1);
}

static int	count_i(t_philo *ph, int flag, int n)
{
	if (ph->all->count_eat)
	{
		if (sem_wait(ph->all->print))
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
		if (sem_post(ph->all->print))
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
		if (sem_wait(ph->all->fork) || sem_wait(ph->all->fork))
			pthread_exit(0);
		ph->t_eat = get_t(ph->all);
		if (ph->t_eat == -1)
			pthread_exit(0);
		if (!print(ph->all, "has taken a fork", ph->t_eat, ph->id) || \
			!print(ph->all, "is eating", ph->t_eat, ph->id))
			pthread_exit(0);
		if (!my_sleep(ph->all, ph->all->t_eat) || \
			sem_post(ph->all->fork) || sem_post(ph->all->fork))
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
				if (sem_wait(p[i]->all->print))
					print(p[i]->all, "error", get_t(p[i]->all), 0000000000);
				pthread_exit(0);
			}
		}
	}
}

int	live(t_philo **p, int i)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	p[0]->all->fork = sem_open("/fork", O_CREAT, 0666, p[0]->all->count_philo);
	p[0]->all->print = sem_open("/print", O_CREAT, 0666, 1);
	if (p[0]->all->fork == SEM_FAILED || p[0]->all->print == SEM_FAILED)
		return (0);
	if (pthread_create(&p[0]->all->t, NULL, cracken, (void *)p))
		return (0);
	while (p[++i] != NULL)
	{
		if (pthread_create(&p[i]->t, NULL, thread, (void *)p[i]))
			return (0);
		usleep(10);
	}
	if (pthread_join(p[0]->all->t, NULL))
		return (0);
	return (1);
}
