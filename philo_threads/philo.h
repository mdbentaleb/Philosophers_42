/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:30 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/18 15:09:49 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int				nb;
	unsigned long	last_meal;
	int				eaten_count;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	eaten_count_mtx;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	unsigned long	time2die;
	unsigned long	time2eat;
	unsigned long	time2sleep;
	unsigned long	start_time;
	unsigned long	tktime;
	int				must_eat;
	int				simulation_running;

	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	struct s_philo	*philos;
}	t_data;

int				ft_start_threads(t_data *data);
int				ft_init_all(t_data *dt);
unsigned long	ft_get_time(void);
int				ft_print(char *msg);
void			ft_print_action(t_philo *philo, char *action);
int				ft_join_threads(t_data *data);
int				ft_start_monitor(t_data *dt, pthread_t *monitor);
void			ft_destroy_all(t_data *dt);
int				ft_isdigit(int c);
long			ft_atoi(const char *str);
void			*ft_philos_routine(void	*args);

void			ft_set_simulation_running(t_data *data, int value);
int				ft_get_simulation_running(t_data *data);

unsigned long	ft_get_last_meal(t_philo *philo);
int				ft_get_eaten_count(t_philo *philo);
void			ft_sleep(t_philo *philo, unsigned long duration);

#endif