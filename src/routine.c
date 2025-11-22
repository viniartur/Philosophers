/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:00 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:02 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (p->left_fork < p->right_fork)
	{
		first_fork = p->left_fork;
		second_fork = p->right_fork;
	}
	else
	{
		first_fork = p->right_fork;
		second_fork = p->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_log(p, FORK_MSG);
	pthread_mutex_lock(second_fork);
	print_log(p, FORK_MSG);
}

static void	let_go_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	philo_eat(t_philo *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->philo_lock);
	p->last_meal = get_time_ms();
	p->eat_count++;
	pthread_mutex_unlock(&p->philo_lock);
	print_log(p, EAT_MSG);
	ft_usleep(p->config->t_eat);
	let_go_forks(p);
}

static void	philo_sleep(t_philo *p)
{
	print_log(p, SLEEP_MSG);
	ft_usleep(p->config->t_sleep);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		ft_usleep(p->config->t_eat);
	while (1)
	{
		if (get_simulation_status(p))
			break ;
		philo_eat(p);
		if (get_simulation_status(p))
			break ;
		philo_sleep(p);
		if (get_simulation_status(p))
			break ;
		print_log(p, THINK_MSG);
	}
	return (NULL);
}
