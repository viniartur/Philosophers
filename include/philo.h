/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvieira <vvieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 15:30:21 by vvieira           #+#    #+#             */
/*   Updated: 2025/11/22 15:30:22 by vvieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK_MSG "\033[1;33m 🍴 has taken a fork\033[0m"
# define EAT_MSG "\033[1;32m 🍽️  is eating\033[0m"
# define SLEEP_MSG "\033[1;35m 💤 is sleeping\033[0m"
# define THINK_MSG "\033[1;34m 🤔 is thinking\033[0m"
# define DIE_MSG "\033[1;31m 💀 died\033[0m"

typedef struct s_configuration
{
	int					philo_count;
	uint64_t			t_die;
	uint64_t			t_eat;
	uint64_t			t_sleep;
	int					times_to_eat;
	int					is_dead;
	uint64_t			start_time;
	pthread_mutex_t		*forks;
	struct s_philos		*philosophers;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		death_lock;
}	t_config;

typedef struct s_philos
{
	t_config			*config;
	uint64_t			last_meal;
	int					id;
	int					eat_count;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			tid;
	pthread_mutex_t		philo_lock;
}						t_philo;

int			ft_atoi(const char *ptr);
int			init_all(char **av, int ac, t_config *config);
uint64_t	get_time_ms(void);
void		free_all(t_config *config);
void		ft_usleep(uint64_t time);
void		print_log(t_philo *p, char *msg);
int			get_simulation_status(t_philo *p);
void		wait_for_completion(t_config *config);
void		*routine(void *arg);
int			start_simulation(t_config *conf);
void		join_threads(t_config *conf);

#endif