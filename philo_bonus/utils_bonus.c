/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:30:00 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/20 19:04:11 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *str)
{
	int			i;
	long long	res;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647 || res < -2147483648)
			return (0);
		i++;
	}
	return (res);
}

unsigned long	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_print_action(t_philo *philo, char *action, t_data *data)
{
	unsigned long	now;

	sem_wait(data->print_sem);
	now = ft_get_time() - data->start_time;
	printf("%lu %d %s\n", now, philo->nb, action);
	sem_post(data->print_sem);
}

void	ft_kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
}
