/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:40 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:28:05 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_struct(t_all *all, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->t_eat = get_t(all);
	if (philo->t_eat == -1)
		return (0);
	philo->i = 0;
	philo->status = 0;
	philo->all = all;
	return (1);
}

static int	init_array(t_all *all, t_philo **philo, int i)
{
	while (++i < all->count_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i] || !init_struct(all, philo[i], i))
			return (0);
	}
	philo[i] = NULL;
	return (1);
}

static int	parse(char **argv, t_all *all, int i, int j)
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
	gettimeofday(&all->start_t, NULL);
	all->end = 0;
	all->print = malloc(sizeof(sem_t));
	all->fork = malloc(sizeof(sem_t));
	if (!all->print || !all->fork)
		return (0);
	if (argv[4])
		ft_atoi(argv[4], &all->count_eat);
	else
		all->count_eat = 0;
	if (all->count_philo < 2 || all->t_dead < 1 || \
		all->t_eat < 1 || all->t_sleep < 1 || all->count_eat < 0)
		return (0);
	return (1);
}

static int	simulation(char **argv)
{
	t_all	all;
	t_philo	**philo;

	if (!parse(argv, &all, -1, -1))
		return (0);
	philo = malloc(sizeof(t_philo *) * (all.count_philo + 1));
	if (!philo || !init_array(&all, philo, -1))
		return (0);
	if (!live(philo, -1))
		return (0);
	my_free(philo);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (!simulation(&argv[1]))
		return (1);
	return (0);
}
