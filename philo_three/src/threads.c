/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:56 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:21:45 by acaryn           ###   ########.fr       */
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
	if (ft_strncmp(str, "is dead", 7))
		if (sem_post(all->print) != 0)
			return (0);
	return (1);
}

static void	*cracken(void *buf)
{
	t_philo	*p;
	long	buf_time;

	p = buf;
	if (pthread_detach(p->t))
		pthread_exit(0);
	while (1)
	{
		buf_time = get_t(p->all) - (p->t_eat + p->all->t_dead);
		if (buf_time > 0)
		{
			print(p->all, "is dead", get_t(p->all), p->id);
			sem_post(p->all->kill);
			pthread_exit(0);
		}
	}
}

static void	*count_eat(void *buf)
{
	int		i;
	t_philo	**p;

	p = buf;
	i = -1;
	while (p[++i])
		if (sem_wait(p[i]->status))
			pthread_exit(0);
	sem_wait(p[0]->all->print);
	sem_post(p[0]->all->kill);
	pthread_exit(0);
}

static void	*thread(void *buf)
{
	t_philo			*ph;	

	ph = buf;
	if (pthread_create(&ph->t, NULL, cracken, (void *)ph))
		return (0);
	while (1)
	{
		if (sem_wait(ph->all->fork) || sem_wait(ph->all->fork))
			exit(0);
		ph->t_eat = get_t(ph->all);
		if (ph->t_eat == -1)
			exit(0);
		if (!print(ph->all, "has taken a fork", ph->t_eat, ph->id) || \
			!print(ph->all, "is eating", ph->t_eat, ph->id))
			exit(0);
		if (!my_sleep(ph->all, ph->all->t_eat) || \
			sem_post(ph->all->fork) || sem_post(ph->all->fork))
			exit(0);
		if ((++ph->i && !count_i(ph)) || !print(ph->all, "is sleeping", \
			get_t(ph->all), ph->id) || !my_sleep(ph->all, ph->all->t_sleep) \
			|| !print(ph->all, "is thinking", get_t(ph->all), ph->id))
			exit(0);
	}
}

int	live(t_philo **p, int i)
{
	pid_t	pid[200];

	if (p[0]->all->count_eat != 0)
		if (pthread_create(&p[0]->all->t, NULL, count_eat, (void *)p))
			return (0);
	while (p[++i] != NULL)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		if (!pid[i])
			thread(p[i]);
	}
	i = -1;
	if (sem_wait(p[0]->all->kill))
		return (0);
	while (p[++i] != NULL)
		kill(pid[i], SIGKILL);
	return (1);
}
