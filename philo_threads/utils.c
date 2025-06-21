/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:19 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/20 19:01:21 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_print_action(t_philo *philo, char *action)
{
	unsigned long	nw;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (ft_get_simulation_running(philo->data))
	{
		nw = ft_get_time() - philo->data->start_time;
		printf("%lu %d %s\n", nw, philo->nb, action);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_sleep(t_philo *philo, unsigned long time)
{
	unsigned long	start;
	unsigned long	check;

	start = ft_get_time();
	while (ft_get_simulation_running(philo->data))
	{
		check = ft_get_time() - start;
		if (check >= time)
			break ;
		usleep(500);
	}
}
