/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:35:51 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/18 15:47:13 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_philo(t_data *dt, int i, int *meals_count)
{
	unsigned long	now;
	unsigned long	last_meal;
	int				eaten_count;

	now = ft_get_time();
	last_meal = ft_get_last_meal(&dt->philos[i]);
	if (now - last_meal >= dt->time2die)
	{
		pthread_mutex_lock(&dt->print_mutex);
		if (ft_get_simulation_running(dt))
		{
			printf("%lu %d died\n", now - dt->start_time, dt->philos[i].nb);
			ft_set_simulation_running(dt, 0);
		}
		pthread_mutex_unlock(&dt->print_mutex);
		return (1);
	}
	if (dt->must_eat > 0)
	{
		eaten_count = ft_get_eaten_count(&dt->philos[i]);
		if (eaten_count >= dt->must_eat)
			(*meals_count)++;
	}
	return (0);
}

void	*ft_death_monitor(void *arg)
{
	t_data			*dt;
	int				i;
	int				meals_count;

	dt = (t_data *)arg;
	usleep(1000);
	while (ft_get_simulation_running(dt))
	{
		meals_count = 0;
		i = 0;
		while (i < dt->philo_count && ft_get_simulation_running(dt))
		{
			if (ft_check_philo(dt, i, &meals_count))
				return (NULL);
			i++;
		}
		if (dt->must_eat > 0 && meals_count == dt->philo_count)
		{
			ft_set_simulation_running(dt, 0);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	ft_start_monitor(t_data *dt, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, ft_death_monitor, dt) != 0)
		return (ft_print("Failed to create monitor thread"));
	pthread_join(*monitor, NULL);
	return (0);
}
