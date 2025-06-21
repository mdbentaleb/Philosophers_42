/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:34 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/18 15:36:48 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_simulation_running(t_data *data, int value)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->simulation_running = value;
	pthread_mutex_unlock(&data->sim_mutex);
}

int	ft_get_simulation_running(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->sim_mutex);
	result = data->simulation_running;
	pthread_mutex_unlock(&data->sim_mutex);
	return (result);
}

unsigned long	ft_get_last_meal(t_philo *philo)
{
	unsigned long	last_meal;

	pthread_mutex_lock(&philo->last_meal_mtx);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mtx);
	return (last_meal);
}

int	ft_get_eaten_count(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->eaten_count_mtx);
	count = philo->eaten_count;
	pthread_mutex_unlock(&philo->eaten_count_mtx);
	return (count);
}
