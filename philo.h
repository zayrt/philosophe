/*
** philo.h for philo in /home/zellou_i/rendu/PSU_2013_philo
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Sun Mar 23 01:28:52 2014 ilyas zelloufi
** Last update Thu Mar 27 16:13:15 2014 ilyas zelloufi
*/

#ifndef			PHILO_H__
# define		PHILO_H__

#include		<pthread.h>

# define		PHILOS		8
# define		RICE		20
# define		ACTION_TIME	1

typedef enum		e_action
  {
    EAT,
    THINK,
    REST
  }			e_action;

typedef struct		s_philos
{
  int			nb;
  int			nb_sticks;
  struct s_philos	*friend;
  struct s_table	*table;
  e_action		state;
}			t_philos;

typedef struct		s_table
{
  t_philos		philos[PHILOS];
  pthread_mutex_t	sticks[PHILOS];
  pthread_mutex_t	rice_mutex;
  int			rice;
}			t_table;

int			use_rice(t_table*, int);
void			eat(t_philos*);
void			think(t_philos*);
void			rest(t_philos*);
void			*manage_table(void*);
int			init_table(t_table*);
void			del_table(t_table*);

#endif			/* !PHILO_H__ */
