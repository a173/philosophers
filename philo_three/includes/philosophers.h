/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaryn <acaryn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:12:29 by acaryn            #+#    #+#             */
/*   Updated: 2021/04/10 17:18:04 by acaryn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_all
{
	sem_t			*print;
	sem_t			*fork;
	sem_t			*kill;
	pthread_t		t;
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
	char			*name;
	int				i;
	long			t_eat;
	sem_t			*status;
	pthread_t		t;
	t_all			*all;
}					t_philo;
int					ft_strncmp(const char *str1, const char *str2, size_t n);
char				*ft_itoa(int n);
int					fill_all(char **argv, t_all *all, int i, int j);
int					ft_atoi(char *line, int *nb);
long				get_t(t_all *all);
int					count_i(t_philo *ph);
int					my_sleep(t_all *all, long n);
int					live(t_philo **philo, int i);
void				my_free(t_philo **philo);

#endif
