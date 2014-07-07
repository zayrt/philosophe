/*
** main.c for  in /home/zellou_i/rendu/PSU_2013_philo
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Mon Jul  7 13:11:15 2014 ilyas zelloufi
** Last update Mon Jul  7 13:11:17 2014 ilyas zelloufi
*/

#include	<stdio.h>
#include	"philo.h"

int		init_table(t_table *table)
{
  int		i;

  i = 0;
  table->rice = RICE;
  if (pthread_mutex_init(&table->rice_mutex, NULL) != 0)
    return (-1);
  while (i != PHILOS)
    {
      if (i % 2 == 0)
	table->philos[i].nb_sticks = 2;
      else
	table->philos[i].nb_sticks = 0;
      table->philos[i].nb = i + 1;
      table->philos[i].table = table;
      table->philos[i].friend = &table->philos[i + 1];
      if (pthread_mutex_init(&table->sticks[i], NULL) != 0)
	return (-1);
      i += 1;
    }
  if (PHILOS % 2 != 0)
    table->philos[PHILOS - 1].nb_sticks = 1;
  table->philos[PHILOS - 1].friend = &table->philos[0];
  return (0);
}

void		del_table(t_table *table)
{
  int		i;

  i = 0;
  if (pthread_mutex_destroy(&table->rice_mutex) != 0)
    fprintf(stderr, "Failed to destroy a mutex\n");
  while (i != PHILOS)
    {
      if (pthread_mutex_destroy(&table->sticks[i]) != 0)
	fprintf(stderr, "Failed to destroy a mutex\n");
      i += 1;
    }
}

int		main(void)
{
  t_table	table;
  pthread_t	threads[PHILOS];
  int		i;

  i = 0;
  if (init_table(&table) == -1)
    {
      fprintf(stderr, "Error in mutex initialization\n");
      return (-1);
    }
  while (i != PHILOS)
    {
      if (pthread_create(&threads[i], NULL, &manage_table, &table.philos[i]))
	{
	  fprintf(stderr, "Failed to create a thread\n");
	  del_table(&table);
	  return (-1);
	}
      i += 1;
    }
  i = 0;
  while (i != PHILOS)
    pthread_join(threads[i++], NULL);
  del_table(&table);
  return (0);
}
