/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:11 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:12 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_entrance(char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0)
		return (printf("Invalid philosophers number\n"), 0);
	if (ft_atoi(av[2]) <= 0)
		return (printf("Invalid time to die \n"), 0);
	if (ft_atoi(av[3]) <= 0)
		return (printf("Invalid time to eat\n"), 0);
	if (ft_atoi(av[4]) <= 0)
		return (printf("Invalid time to sleep\n"), 0);
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (printf("Invalid number of t each philosopher must eat\n"), 0);
	return (1);
}

static int	one_philo(t_config *config)
{
	printf("0 1 🍴 has taken a fork\n");
	ft_usleep(config->t_die);
	printf("%lu 1%s\n", config->t_die, DIE_MSG);
	free_all(config);
	return (0);
}

int	start_simulation(t_config *config)
{
	int	i;

	config->start_time = get_time_ms();
	i = -1;
	while (++i < config->philo_count)
	{
		if (pthread_create(&config->philosophers[i].tid, NULL, &routine,
				&config->philosophers[i]))
			return (1);
	}
	return (0);
}

void	join_threads(t_config *config)
{
	int	i;

	i = -1;
	while (++i < config->philo_count)
		pthread_join(config->philosophers[i].tid, NULL);
}

int	main(int ac, char **av)
{
	t_config	config;

	config.philosophers = NULL;
	config.forks = NULL;
	if (ac != 5 && ac != 6)
		return (printf("Wrong argument count\n"), 1);
	if (check_entrance(av) == 0)
		return (1);
	if (init_all(av, ac, &config))
		return (free_all(&config), 1);
	if (config.philo_count == 1)
		return (one_philo(&config));
	if (start_simulation(&config))
	{
		free_all(&config);
		return (1);
	}
	wait_for_completion(&config);
	join_threads(&config);
	free_all(&config);
	return (0);
}
