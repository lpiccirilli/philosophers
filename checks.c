/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicciri <lpicciri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:47:32 by lpicciri          #+#    #+#             */
/*   Updated: 2024/03/01 15:59:36 by lpicciri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ')
			{
				j++;
				continue ;
			}
			if ((argv[i][j] < 48 || argv[i][j] > 57))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	if (only_digits(argv) == -1)
		return (-1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

void	*ciao(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	messages ("has taken a fork", philo);
	ft_usleep(philo->t_die + 1);
	printf("%llu %d died\n", philo->t_die, philo->id);
	return (NULL);
}

int	case_one(t_data *data)
{
	pthread_t	one;

	data->start_time = get_time();
	if (pthread_create(&one, NULL, &ciao, &data->philo[0]))
		return (-1);
	pthread_join(one, NULL);
	return (0);
}
