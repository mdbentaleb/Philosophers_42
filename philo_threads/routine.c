/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:23 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/24 11:11:45 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_update_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->last_meal_mtx);
}

static void	ft_meals_increment(t_philo *philo)
{
	pthread_mutex_lock(&philo->eaten_count_mtx);
	philo->eaten_count++;
	pthread_mutex_unlock(&philo->eaten_count_mtx);
}

void	ft_eating(t_philo *philo)
{
	if (!ft_get_simulation_running(philo->data))
		return ;
	pthread_mutex_lock(philo->l_fork);
	if (!ft_get_simulation_running(philo->data))
		return ((void)pthread_mutex_unlock(philo->l_fork));
	ft_print_action(philo, "has taken a fork");
	if (philo->data->philo_count == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		return (ft_sleep(philo, philo->data->time2die));
	}
	pthread_mutex_lock(philo->r_fork);
	if (!ft_get_simulation_running(philo->data))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ((void)pthread_mutex_unlock(philo->l_fork));
	}
	ft_print_action(philo, "has taken a fork");
	ft_print_action(philo, "is eating");
	ft_update_last_meal(philo);
	ft_sleep(philo, philo->data->time2eat);
	ft_meals_increment(philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static int	ft_sleep_think(t_philo *philo)
{
	unsigned long	think_time;

	ft_print_action(philo, "is sleeping");
	ft_sleep(philo, philo->data->time2sleep);
	if (!ft_get_simulation_running(philo->data))
		return (1);
	ft_print_action(philo, "is thinking");
	if (philo->data->philo_count % 2 == 1)
	{
		think_time = (philo->data->time2eat - philo->data->time2sleep) / 2;
		if (think_time > 0)
			ft_sleep(philo, think_time);
	}
	return (0);
}

void	*ft_philos_routine(void	*args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	if (philo->nb % 2 == 0)
		ft_sleep(philo, philo->data->time2sleep / 2);
	while (ft_get_simulation_running(philo->data))
	{
		ft_eating(philo);
		if (!ft_get_simulation_running(philo->data))
			break ;
		if (ft_sleep_think(philo))
			break ;
		if (!ft_get_simulation_running(philo->data))
			break ;
	}
	return (NULL);
}
