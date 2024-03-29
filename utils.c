/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:09:12 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/01 16:05:09 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	while (is_in_strings(*(char *) str, "\t\n\v\f\r "))
		str++;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (result * 10 < 0)
			return (-1);
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}

bool	is_in_strings(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (true);
		str++;
	}
	return (false);
}

int	ft_usleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->eat_lock);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp (str, "died") != 0 && philo->data->died == 0)
		printf("%llu %d %s\n", time, philo->id, str);
	if (ft_strcmp (str, "died") == 0 && philo->data->died == 0)
	{
		philo->data->died = 1;
		printf("%llu %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->eat_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return ;
}
