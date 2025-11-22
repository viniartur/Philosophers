/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:05 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:07 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_simulation_status(t_philo *p)
{
	int	status;

	pthread_mutex_lock(&p->config->death_lock);
	status = p->config->is_dead;
	pthread_mutex_unlock(&p->config->death_lock);
	return (status);
}

static int	check_death(t_config *config)
{
	int		i;
	size_t	current_time;

	i = -1;
	while (++i < config->philo_count)
	{
		pthread_mutex_lock(&config->philosophers[i].philo_lock);
		current_time = get_time_ms();
		if ((current_time - config->philosophers[i].last_meal) > config->t_die)
		{
			print_log(&config->philosophers[i], DIE_MSG);
			pthread_mutex_unlock(&config->philosophers[i].philo_lock);
			return (1);
		}
		pthread_mutex_unlock(&config->philosophers[i].philo_lock);
	}
	return (0);
}

static int	check_meals_completed(t_config *conf)
{
	int	i;
	int	meals_completed;

	if (conf->times_to_eat == -1)
		return (0);
	meals_completed = 0;
	i = -1;
	while (++i < conf->philo_count)
	{
		pthread_mutex_lock(&conf->philosophers[i].philo_lock);
		if (conf->philosophers[i].eat_count >= conf->times_to_eat)
			meals_completed++;
		pthread_mutex_unlock(&conf->philosophers[i].philo_lock);
	}
	if (meals_completed == conf->philo_count)
	{
		print_log(&conf->philosophers[0], "All philosophers are full");
		pthread_mutex_lock(&conf->death_lock);
		conf->is_dead = 1;
		pthread_mutex_unlock(&conf->death_lock);
		return (1);
	}
	return (0);
}

void	wait_for_completion(t_config *config)
{
	while (1)
	{
		if (check_meals_completed(config))
			break ;
		if (check_death(config))
			break ;
		ft_usleep(2);
	}
}
