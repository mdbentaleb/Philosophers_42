/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:09:52 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/23 11:07:28 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sleep(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	unsigned long	current;

	start = ft_get_time();
	while (1)
	{
		current = ft_get_time();
		if (current - start >= time)
			break ;
		if (ft_check_death(philo))
			exit(1);
		usleep(1000);
	}
}

void	ft_wait_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->pids[i] > 0)
			waitpid(data->pids[i], &status, 0);
		i++;
	}
}

void	ft_eating(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	ft_print_action(philo, "has taken a fork", data);
	if (data->philo_count == 1)
	{
		ft_sleep(philo, data->time2die);
		sem_post(data->forks);
		exit (0);
	}
	sem_wait(data->forks);
	ft_print_action(philo, "has taken a fork", data);
	philo->last_meal = ft_get_time();
	ft_print_action(philo, "is eating", data);
	ft_sleep(philo, data->time2eat);
	philo->eaten_count++;
	sem_post(data->forks);
	sem_post(data->forks);
}
