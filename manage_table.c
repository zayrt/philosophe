/*
** manage_table.c for  in /home/zellou_i/rendu/PSU_2013_philo
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Mon Jul  7 13:11:07 2014 ilyas zelloufi
** Last update Mon Jul  7 13:11:08 2014 ilyas zelloufi
*/

#include	<unistd.h>
#include	<stdio.h>
#include	"philo.h"

int		use_rice(t_table *table, int to_eat)
{
  int		to_ret;

  pthread_mutex_lock(&table->rice_mutex);
  table->rice -= to_eat;
  to_ret = table->rice;
  pthread_mutex_unlock(&table->rice_mutex);
  return (to_ret);
}

void		eat(t_philos *p)
{
  pthread_mutex_lock(&p->table->sticks[p->nb - 1]);
  pthread_mutex_lock(&p->table->sticks[p->friend->nb - 1]);
  p->state = EAT;
  if (use_rice(p->table, 0) > 0)
    {
      printf("Le philosphe %d a mange, il reste %d portions de riz.\n", p->nb,
	     use_rice(p->table, 1));
      fflush(stdout);
    }
  else
    {
      pthread_mutex_unlock(&p->table->sticks[p->nb - 1]);
      pthread_mutex_unlock(&p->table->sticks[p->friend->nb - 1]);
      return ;
    }
  sleep(ACTION_TIME);
  p->nb_sticks -= 1;
  p->friend->nb_sticks += 1;
  pthread_mutex_unlock(&p->table->sticks[p->nb - 1]);
  pthread_mutex_unlock(&p->table->sticks[p->friend->nb - 1]);
}

void		think(t_philos *p)
{
  pthread_mutex_lock(&p->table->sticks[p->nb - 1]);
  p->state = THINK;
  printf("Le philosphe %d reflechit.\n", p->nb);
  fflush(stdout);
  sleep(ACTION_TIME);
  pthread_mutex_unlock(&p->table->sticks[p->nb - 1]);
  pthread_mutex_lock(&p->table->sticks[p->friend->nb - 1]);
  if (p->friend->nb_sticks >= 1 && p->friend->state != THINK)
    {
      p->nb_sticks += 1;
      p->friend->nb_sticks -= 1;
    }
  pthread_mutex_unlock(&p->table->sticks[p->friend->nb - 1]);
}

void		rest(t_philos *p)
{
  p->state = REST;
  printf("Le philosphe %d se repose.\n", p->nb);
  fflush(stdout);
  pthread_mutex_lock(&p->table->sticks[p->friend->nb - 1]);
  if (p->friend->nb_sticks >= 1 && p->friend->state != THINK)
    {
      p->nb_sticks += 1;
      p->friend->nb_sticks -= 1;
    }
  pthread_mutex_unlock(&p->table->sticks[p->friend->nb - 1]);
}

void		*manage_table(void *arg)
{
  t_philos	p;

  p = *(t_philos*) arg;
  while (use_rice(p.table, 0) > 0)
    {
      printf("Le philosphe %d a %d baguette(s).\n", p.nb, p.nb_sticks);
      fflush(stdout);
      if (p.nb_sticks == 2)
	eat(&p);
      else if (p.nb_sticks == 1)
	think(&p);
      else
	rest(&p);
    }
  pthread_exit(0);
}
