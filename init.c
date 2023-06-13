/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msintas- <msintas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 13:12:28 by msintas-          #+#    #+#             */
/*   Updated: 2023/06/12 13:03:36 by msintas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Initialize specific data for each thread.
Assign each philosopher a number, starting from 1, and the two nearest forks,
starting from 0. Connect the "philo struct" with the "data struct" to have access
from each thread to the main program data and fill this pointer with struct data.
*/

void ft_init_philos(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_of_philos)
    {
        // tiene que empezar por 1 el número de filosofo
        data->philosophers[i].philo_num = i + 1;
        data->philosophers[i].fork_left = i;
        data->philosophers[i].fork_right = (i + 1) % data->num_of_philos;
        data->philosophers[i].generic_data = data;
        data->philosophers[i].philo_ko = 0;
        i++;
    }
}


/*
Initialize generic data for the program. If any of the values is less than 0
the program will not run.
*/
void ft_init_data(int argc, char **argus, t_data *data)
{
    data->num_of_philos = ft_atoi(argus[0]);
    data->num_of_forks = data->num_of_philos;
    data->philosophers = malloc(sizeof(t_philo) * data->num_of_philos);
    if (data->philosophers == NULL)
        return ;
    data->mutexes = malloc(sizeof(pthread_mutex_t) * (data->num_of_philos));
    if (data->mutexes == NULL)
        return ;
    data->time_to_die = ft_long_atoi(argus[1]);
    data->time_to_eat = ft_long_atoi(argus[2]);
    data->time_to_sleep = ft_long_atoi(argus[3]);
    if (argc == 6)
    {
        data->num_must_eat = ft_long_atoi(argus[4]);
        if (data->num_must_eat < 0)
            return;
    }
    if (data->num_of_philos < 0 || data->time_to_die < 0 || data->time_to_eat < 0 \
     || data->time_to_sleep < 0) {
        return ;
    }
    //data->some_philo_ko = 0;
}

/* Initialize all mutexes */

void ft_init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_init(&data->mutexes[i], NULL);
        //pthread_mutex_init(&data->philosophers[i].write_mutex, NULL);
        //pthread_mutex_init(&data->philosophers[i].check_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].last_ate_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].philo_ko_mutex, NULL);
        pthread_mutex_init(&data->philosophers[i].current_time_mutex, NULL);
        i++;   
    }
    //pthread_mutex_init(&data->write_mutex, NULL);

}


/* Destroy mutexes */

void ft_destroy_mutexes(t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->num_of_philos)
    {
        pthread_mutex_destroy(&data->mutexes[i]);
        //pthread_mutex_destroy(&data->philosophers[i].write_mutex);
        //pthread_mutex_destroy(&data->philosophers[i].check_mutex);
        pthread_mutex_destroy(&data->philosophers[i].last_ate_mutex);
        pthread_mutex_destroy(&data->philosophers[i].philo_ko_mutex);
        pthread_mutex_destroy(&data->philosophers[i].current_time_mutex);
        printf("mutexes destroyed\n");
        i++;
    }
    //pthread_mutex_destroy(&data->write_mutex);
}