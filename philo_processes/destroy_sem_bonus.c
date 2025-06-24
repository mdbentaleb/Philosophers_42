/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_semaphores.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/19 13:27:42 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_all(t_data *dt)
{
	if (dt->forks != SEM_FAILED && dt->forks != NULL)
	{
		sem_close(dt->forks);
		sem_unlink("/forks_sem");
	}
	if (dt->print_sem != SEM_FAILED && dt->print_sem != NULL)
	{
		sem_close(dt->print_sem);
		sem_unlink("/print_sem");
	}
	if (dt->meal_check != SEM_FAILED && dt->meal_check != NULL)
	{
		sem_close(dt->meal_check);
		sem_unlink("/meal_check_sem");
	}
	if (dt->death_sem != SEM_FAILED && dt->death_sem != NULL)
	{
		sem_close(dt->death_sem);
		sem_unlink("/death_sem");
	}
	if (dt->philos)
		free(dt->philos);
	if (dt->pids)
		free(dt->pids);
}
