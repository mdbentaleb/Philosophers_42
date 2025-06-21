/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:47 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/19 13:30:49 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_all(t_data *dt)
{
	int	i;

	if (dt->forks)
	{
		i = -1;
		while (++i < dt->philo_count)
			pthread_mutex_destroy(&dt->forks[i]);
		free(dt->forks);
	}
	if (dt->philos)
	{
		i = -1;
		while (++i < dt->philo_count)
		{
			pthread_mutex_destroy(&dt->philos[i].last_meal_mtx);
			pthread_mutex_destroy(&dt->philos[i].eaten_count_mtx);
		}
		free(dt->philos);
	}
	pthread_mutex_destroy(&dt->print_mutex);
	pthread_mutex_destroy(&dt->sim_mutex);
}
