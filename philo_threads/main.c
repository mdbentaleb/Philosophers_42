/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moben-ta <moben-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:14:39 by moben-ta          #+#    #+#             */
/*   Updated: 2025/06/17 14:29:57 by moben-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	ft_check_args_help(char *av)
{
	int	i;

	if (!av || !av[0])
		return (1);
	i = 0;
	while (av[i] == ' ' || av[i] == '\t')
		i++;
	if (!av[i])
		return (1);
	if (av[i] == '+')
		i++;
	if (!ft_isdigit(av[i]))
		return (1);
	while (ft_isdigit(av[i]))
		i++;
	while (av[i] == ' ' || av[i] == '\t')
		i++;
	if (av[i] != '\0')
		return (1);
	return (0);
}

int	ft_check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_check_args_help(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_data(t_data *dt, int arc, char **arv)
{
	if (arc != 5 && arc != 6)
		return (ft_print("Usage: ./philo Nphilos Tdie Teat Tsleep Meals"));
	if (ft_check_args(arv))
		return (ft_print("Error: Invalid inputs."));
	dt->philo_count = ft_atoi(arv[1]);
	if (!(dt->philo_count >= 1 && dt->philo_count <= 200))
		return (ft_print("Error: number of philos must be between 1 ~ 200."));
	dt->time2die = ft_atoi(arv[2]);
	dt->time2eat = ft_atoi(arv[3]);
	dt->time2sleep = ft_atoi(arv[4]);
	if (dt->time2die < 60 || dt->time2eat < 60 || dt->time2sleep < 60)
		return (ft_print("Error: time (die/eat/sleep) [60 ≤ T ≤ INT_MAX]."));
	if (arc == 6)
	{
		dt->must_eat = ft_atoi(arv[5]);
		if (dt->must_eat < 0)
			return (ft_print("Error: number of meals must be at least 1."));
		else if (dt->must_eat == 0)
			return (2);
	}
	else
		dt->must_eat = -1;
	return (0);
}

int	main(int arc, char **arv)
{
	t_data		dt;
	pthread_t	monitor;
	int			check;

	memset(&dt, 0, sizeof(t_data));
	check = ft_init_data(&dt, arc, arv);
	if (check == 1)
		return (1);
	else if (check == 2)
		return (0);
	if (ft_init_all(&dt))
		return (ft_destroy_all(&dt), 1);
	if (ft_start_threads(&dt))
		return (ft_destroy_all(&dt), 1);
	if (ft_start_monitor(&dt, &monitor))
		return (ft_destroy_all(&dt), 1);
	ft_join_threads(&dt);
	ft_destroy_all(&dt);
	return (0);
}
