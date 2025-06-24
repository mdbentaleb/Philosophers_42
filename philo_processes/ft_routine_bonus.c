/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/24 11:11:21 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_check_death(t_philo *philo)
{
	t_data			*data;
	unsigned long	current_time;
	unsigned long	time_since_meal;

	data = philo->data;
	current_time = ft_get_time();
	time_since_meal = current_time - philo->last_meal;
	if (time_since_meal >= data->time2die)
	{
		sem_wait(data->print_sem);
		printf("%lu %d died\n", current_time - data->start_time, philo->nb);
		sem_post(data->death_sem);
		return (1);
	}
	return (0);
}

int	ft_check_meals_complete(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->must_eat > 0 && philo->eaten_count > data->must_eat)
	{
		sem_wait(data->meal_check);
		exit(0);
	}
	return (0);
}

void	*ft_death_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_check_death(philo))
			exit(1);
		usleep(1000);
	}
	return (NULL);
}

int	ft_philo_process(t_philo *philo)
{
	t_data		*data;
	pthread_t	death_thread;

	data = philo->data;
	philo->last_meal = data->start_time;
	if (pthread_create(&death_thread, NULL, ft_death_monitor, philo) != 0)
		return (1);
	pthread_detach(death_thread);
	if (philo->nb % 2 == 0)
		ft_sleep(philo, 1);
	while (1)
	{
		ft_eating(philo, data);
		ft_check_meals_complete(philo);
		ft_print_action(philo, "is sleeping", data);
		ft_sleep(philo, data->time2sleep);
		ft_print_action(philo, "is thinking", data);
		if (data->philo_count % 2 == 1)
			ft_sleep(philo, 1);
	}
	return (0);
}

int	ft_start_processes(t_data *data)
{
	int	i;

	data->start_time = ft_get_time();
	i = 0;
	while (i < data->philo_count)
	{
		data->pids[i] = fork();
		if (data->pids[i] == -1)
			return (ft_print("Failed to create process"));
		if (data->pids[i] == 0)
			if (ft_philo_process(&data->philos[i]))
				return (1);
		i++;
	}
	return (0);
}
