/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/19 13:27:50 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_semaphores(t_data *dt)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/meal_check_sem");
	sem_unlink("/death_sem");
	dt->forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, dt->philo_count);
	if (dt->forks == SEM_FAILED)
		return (ft_print("Failed to create forks semaphore"));
	dt->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (dt->print_sem == SEM_FAILED)
		return (ft_print("Failed to create print semaphore"));
	dt->meal_check = sem_open("/meal_check_sem", O_CREAT | O_EXCL, 0644, 1);
	if (dt->meal_check == SEM_FAILED)
		return (ft_print("Failed to create meal check semaphore"));
	dt->death_sem = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 0);
	if (dt->death_sem == SEM_FAILED)
		return (ft_print("Failed to create death semaphore"));
	return (0);
}

int	ft_init_philos(t_data *dt)
{
	int	i;

	dt->philos = malloc(sizeof(t_philo) * dt->philo_count);
	if (!dt->philos)
		return (ft_print("malloc failed"));
	dt->pids = malloc(sizeof(pid_t) * dt->philo_count);
	if (!dt->pids)
		return (ft_print("malloc failed"));
	i = 0;
	while (i < dt->philo_count)
	{
		dt->philos[i].nb = i + 1;
		dt->philos[i].eaten_count = 0;
		dt->philos[i].last_meal = 0;
		dt->philos[i].data = dt;
		dt->pids[i] = 0;
		i++;
	}
	return (0);
}

int	ft_init_all(t_data *dt)
{
	if (ft_init_semaphores(dt))
		return (1);
	if (ft_init_philos(dt))
		return (1);
	return (0);
}
