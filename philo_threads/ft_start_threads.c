/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:06:07 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/18 15:06:44 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_start_threads(t_data *data)
{
	int	i;

	data->start_time = ft_get_time();
	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].last_meal_mtx);
		data->philos[i].last_meal = data->start_time;
		pthread_mutex_unlock(&data->philos[i].last_meal_mtx);
		if (pthread_create(&data->philos[i].thread, NULL,
				ft_philos_routine, &data->philos[i]) != 0)
			return (ft_print("Failed to create thread"));
	}
	return (0);
}

int	ft_join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}
