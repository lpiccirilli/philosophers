/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luca <luca@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:50:34 by lpicciri          #+#    #+#             */
/*   Updated: 2024/02/28 19:06:37 by luca             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_data *data)
{
	data->start_time = get_time();
	if (pthread_create(&data->thread_id[0], NULL, &routine, &data->philo[0]))
		return (-1);
	pthread_detach(data->thread_id[0]);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&data->died_lock);
	free(data->forks);
	free(data->thread_id);
	free(data->philo);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == -1)
		return (write(1, "Error: wrong arguments\n", 24));
	if (init(&data, argv) == -1)
		return (printf("Error: init_data\n"));
	free_data(&data);
	return (0);
}
