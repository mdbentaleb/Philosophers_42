/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:44 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/20 16:02:31 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *dt)
{
	int	i;

	dt->forks = malloc(sizeof(pthread_mutex_t) * dt->philo_count);
	if (!dt->forks)
		return (ft_print("mem allocation failed"));
	i = -1;
	while (++i < dt->philo_count)
	{
		if (pthread_mutex_init(&dt->forks[i], NULL) != 0)
			return (ft_print("mutex init failed"));
	}
	if (pthread_mutex_init(&dt->print_mutex, NULL) != 0)
		return (ft_print("mutex init failed"));
	if (pthread_mutex_init(&dt->sim_mutex, NULL) != 0)
		return (ft_print("mutex init failed"));
	return (0);
}

int	ft_init_philos(t_data *dt)
{
	int	i;

	dt->philos = malloc(sizeof(t_philo) * dt->philo_count);
	if (!dt->philos)
		return (ft_print("malloc failed (philos)"));
	i = -1;
	while (++i < dt->philo_count)
	{
		dt->philos[i].nb = i + 1;
		dt->philos[i].eaten_count = 0;
		dt->philos[i].last_meal = 0;
		dt->philos[i].l_fork = &dt->forks[i];
		dt->philos[i].r_fork = &dt->forks[(i + 1) % dt->philo_count];
		dt->philos[i].data = dt;
		if (pthread_mutex_init(&dt->philos[i].last_meal_mtx, NULL) != 0)
			return (ft_print("mutex init failed"));
		if (pthread_mutex_init(&dt->philos[i].eaten_count_mtx, NULL) != 0)
			return (ft_print("mutex init failed"));
	}
	return (0);
}

int	ft_init_all(t_data *dt)
{
	if (ft_init_mutex(dt))
		return (1);
	if (ft_init_philos(dt))
		return (1);
	dt->simulation_running = 1;
	dt->start_time = ft_get_time();
	return (0);
}
