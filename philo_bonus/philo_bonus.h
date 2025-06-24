/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/23 12:26:29 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>

typedef struct s_philo
{
	int				nb;
	unsigned long	last_meal;
	int				eaten_count;
	pid_t			pid;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	unsigned long	time2die;
	unsigned long	time2eat;
	unsigned long	time2sleep;
	int				must_eat;
	unsigned long	start_time;

	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*meal_check;
	sem_t			*death_sem;

	struct s_philo	*philos;
	pid_t			*pids;
}	t_data;

int				ft_print(char *msg);
int				ft_init_data(t_data *dt, int arc, char **arv);
void			ft_sleep(t_philo *philo, unsigned long time);
int				ft_isdigit(int c);
long			ft_atoi(const char *str);
unsigned long	ft_get_time(void);
void			ft_print_action(t_philo *philo, char *action, t_data *data);
int				ft_init_all(t_data *dt);
void			ft_destroy_all(t_data *dt);
int				ft_philo_process(t_philo *philo);
int				ft_start_processes(t_data *data);
void			ft_wait_processes(t_data *data);
int				ft_check_death(t_philo *philo);
void			*ft_death_monitor(void *arg);
void			*ft_meal_monitor(void *arg);
void			ft_eating(t_philo *philo, t_data *data);
void			ft_kill_all_processes(t_data *data);

#endif
