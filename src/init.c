/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:16 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:17 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	allocate_memory(t_config *config)
{
	config->philosophers = malloc(sizeof(t_philo) * config->philo_count);
	config->forks = malloc(sizeof(pthread_mutex_t) * config->philo_count);
	if (!config->philosophers || !config->forks)
		return (1);
	return (0);
}

static void	init_mutexes(t_config *config)
{
	int	i;

	pthread_mutex_init(&config->write_lock, NULL);
	pthread_mutex_init(&config->death_lock, NULL);
	i = -1;
	while (++i < config->philo_count)
		pthread_mutex_init(&config->forks[i], NULL);
}

static void	init_philo(t_philo *p, t_config *config, int i)
{
	p->config = config;
	p->id = i + 1;
	p->eat_count = 0;
	p->last_meal = get_time_ms();
	p->left_fork = &config->forks[i];
	p->right_fork = &config->forks[(i + 1) % config->philo_count];
}

int	init_all(char **av, int ac, t_config *config)
{
	int	i;

	config->philo_count = ft_atoi(av[1]);
	config->t_die = ft_atoi(av[2]);
	config->t_eat = ft_atoi(av[3]);
	config->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		config->times_to_eat = ft_atoi(av[5]);
	config->is_dead = 0;
	if (allocate_memory(config))
		return (1);
	init_mutexes(config);
	i = -1;
	while (++i < config->philo_count)
		init_philo(&config->philosophers[i], config, i);
	return (0);
}
