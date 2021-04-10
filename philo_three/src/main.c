/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:11:40 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:20:08 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_struct(t_all *all, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->name = ft_itoa(philo->id);
	if (!philo->name)
		return (0);
	philo->t_eat = get_t(all);
	if (philo->t_eat == -1)
		return (0);
	philo->i = 0;
	philo->status = malloc(sizeof(sem_t));
	sem_unlink(philo->name);
	philo->status = sem_open(philo->name, O_CREAT, 0666, 1);
	if (!philo->status || sem_wait(philo->status))
		return (0);
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

static int	parse(char **argv, t_all *all)
{
	if (!fill_all(argv, all, -1, -1))
		return (0);
	all->print = malloc(sizeof(sem_t));
	all->fork = malloc(sizeof(sem_t));
	all->kill = malloc(sizeof(sem_t));
	if (!all->print || !all->fork)
		return (0);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/kill");
	all->fork = sem_open("/fork", O_CREAT, 0666, all->count_philo);
	all->print = sem_open("/print", O_CREAT, 0666, 1);
	all->kill = sem_open("/kill", O_CREAT, 0666, 1);
	if (all->fork == SEM_FAILED || all->print == SEM_FAILED \
		|| all->kill == SEM_FAILED || sem_wait(all->kill))
		return (0);
	return (1);
}

static int	simulation(char **argv)
{
	t_all	all;
	t_philo	**philo;

	if (!parse(argv, &all))
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
