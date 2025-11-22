/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:29:54 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:29:56 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *ptr)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while ((*ptr >= 9 && *ptr <= 13) || *ptr == 32)
		ptr++;
	if (*ptr == '-' || *ptr == '+')
	{
		if (*ptr == '-')
			sign = -1;
		ptr++;
	}
	while (*ptr >= '0' && *ptr <= '9')
	{
		result = result * 10 + (*ptr - '0');
		ptr++;
	}
	if (*ptr != '\0')
		return (0);
	return (result * sign);
}

void	free_all(t_config *config)
{
	int	i;

	if (config->forks)
	{
		i = -1;
		while (++i < config->philo_count)
			pthread_mutex_destroy(&config->forks[i]);
	}
	pthread_mutex_destroy(&config->write_lock);
	pthread_mutex_destroy(&config->death_lock);
	if (config->philosophers)
		free(config->philosophers);
	if (config->forks)
		free(config->forks);
}

void	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
		usleep(500);
}

uint64_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_log(t_philo *p, char *msg)
{
	const char	*die_msg;
	int			i;

	pthread_mutex_lock(&p->config->write_lock);
	pthread_mutex_lock(&p->config->death_lock);
	if (!p->config->is_dead)
	{
		printf("%lu %d %s\n", get_time_ms() - p->config->start_time, p->id, msg);
		die_msg = DIE_MSG;
		i = 0;
		while (die_msg[i] && msg[i] && die_msg[i] == msg[i])
			i++;
		if (die_msg[i] == '\0' && msg[i] == '\0')
			p->config->is_dead = 1;
	}
	pthread_mutex_unlock(&p->config->death_lock);
	pthread_mutex_unlock(&p->config->write_lock);
}
