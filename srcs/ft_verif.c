/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 06:20:34 by lcharvol          #+#    #+#             */
/*   Updated: 2017/03/08 06:20:36 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snake.h"

int			ft_get_alea()
{
	int i;

	i = (rand()) % SIZE_X;
	return (i);
}

void		ft_verif_wall(t_env *p)
{
	t_snake *s;
	t_wall	*w;

	w = p->wall;
	s = p->snake;
	while (p->wall->next != NULL)
	{
		p->snake = s;
		while (p->snake->next != NULL)
		{
			if (p->snake->pos_x == p->wall->x && p->snake->pos_y == p->wall->y)
			{
				ft_game_over(p);
				p->snake = s;
				p->wall = w;
				return ;
			}
			p->snake = p->snake->next;
		}
		if (p->snake->pos_x == p->wall->x && p->snake->pos_y == p->wall->y)
		{
			ft_game_over(p);
			p->snake = s;
			p->wall = w;
			return ;
		}
		p->wall = p->wall->next;
	}
	if (p->snake->pos_x == p->wall->x && p->snake->pos_y == p->wall->y)
	{
		ft_game_over(p);
		p->snake = s;
		p->wall = w;
		return ;
	}
	p->snake = s;
	p->wall = w;
}

void		ft_verif_coli(t_env *p)
{
	t_snake *tmp;
	int 	tmp_x;
	int 	tmp_y;

	tmp = p->snake;
	tmp_x = p->snake->pos_x;
	tmp_y = p->snake->pos_y;

	if (p->snake->next != NULL)
		p->snake = p->snake->next;
	if (p->snake->next != NULL)
		p->snake = p->snake->next;
	while (p->snake->next != NULL)
	{
		if (tmp_y == p->snake->pos_y && tmp_x == p->snake->pos_x)
		{
			ft_game_over(p);
			p->snake = tmp;
			return ;
		}
		p->snake = p->snake->next;
	}
	p->snake = tmp;
}

int		ft_verif_bonus(int x, int y, t_env *p)
{
	t_snake *new;

	new = p->snake;
	while (p->snake->next != NULL)
	{
		if (p->snake->pos_x == x && p->snake->pos_y == y)
			return (1);
		p->snake = p->snake->next;
	}
	if (p->snake->pos_x == x && p->snake->pos_y == y)
		return (1);
	p->snake = new;
	return (0);
}

void		ft_choose_color(t_env *p)
{
	if (p->level == 3)
	{
		p->r = 100;
		p->v = 5 * p->snake->id;
		p->b = 131;
	}
	if (p->level == 4)
	{
		p->r = 200;
		p->v = 5 * p->snake->id;
		p->b = 50 + (10 * p->snake->id);
	}
	if (p->level == 2)
	{
		p->r = 100;
		p->v = 5 * p->snake->id;
		p->b = 131;
	}
	if (p->level == 1)
	{
		p->r = 255;
		p->v = 5 * p->snake->id;
		p->b = 150;
	}
}

void		ft_check_snake(int i, int i2, t_env *p)
{
	t_snake *tmp;

	tmp = p->snake;
	while (p->snake->next != NULL)
	{
		if (p->snake->pos_x == i2 && p->snake->pos_y == i)
		{
			ft_choose_color(p);
		}
		p->snake = p->snake->next;

	}
	if (p->snake->pos_x == i2 && p->snake->pos_y == i)
	{
		ft_choose_color(p);
	}
	p->snake = tmp;
}