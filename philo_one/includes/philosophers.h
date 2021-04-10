/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:12:29 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/09 15:45:28 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_all
{
	pthread_t		t;
	pthread_mutex_t	*print;
	int				count_philo;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				count_eat;
	int				end;
	struct timeval	start_t;
}					t_all;

typedef struct s_philo
{
	int				id;
	int				i;
	long			t_eat;
	int				status;
	t_all			*all;
	pthread_t		t;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
}					t_philo;

int					ft_atoi(char *line, int *nb);
long				get_t(t_all *all);
int					my_sleep(t_all *all, long n);
int					live(t_philo **philo, int i);
void				my_free(t_philo **philo, int i);

#endif
