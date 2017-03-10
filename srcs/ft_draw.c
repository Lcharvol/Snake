 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 06:24:25 by lcharvol          #+#    #+#             */
/*   Updated: 2017/03/08 06:24:30 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snake.h"


void		ft_draw_square(int start_x, int start_y, int size, t_env *p)
{
	int		i;
	int		i2;
	int		tmp;

	i2 = 0;
	tmp = 0;
	while (i2 < (size * 4))
	{
		i = 0;
		while (i < (size * 4))
		{
			p->ret[i + tmp + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->r;
			p->ret[i + tmp + 1 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->v;
			p->ret[i + tmp + 2 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = p->b;
			p->ret[i + tmp + 3 + ((start_y * WIDTH * 4) +
				(start_x * 4))] = 0;
			i += 4;
		}
		i2 += 4;
		tmp += (WIDTH * 4);
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
			p->r = 60 + i;
			p->v = 76;
			p->b = 231;
		}
		p->snake = p->snake->next;

	}
	if (p->snake->pos_x == i2 && p->snake->pos_y == i)
	{
		p->r = 60;
		p->v = 76;
		p->b = 231;
	}
	p->snake = tmp;
}

int			ft_get_alea()
{
	int i;

	i = (rand()) % 17;
	return (i);
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

void		ft_draw_bonus(t_env *p, int e)
{
	int size;

	size = (WIDTH / SIZE_X) - ((e * SIZE_X) / ((WIDTH / (SIZE_X)) - (2 * e)));
	size -= (size * 0.7);
	if (p->bonus_x == p->snake->pos_x && p->bonus_y == p->snake->pos_y)
	{
		p->bonus_x = ft_get_alea();
		p->bonus_y = ft_get_alea();
		p->snake = ft_add_snake(p, p->bonus_x, p->bonus_y);
	}
	p->r = 60;
	p->v = 76;
	p->b = 231;
	ft_draw_square((p->bonus_x * (WIDTH / SIZE_X)) + (e + size + 1), p->bonus_y * (HEIGHT / SIZE_Y) + (e + size + 1), size, p);

}

void		ft_draw_map(t_env *p)
{
	int i;
	int i2;
	int size;
	int e;

	i = -1;
	e = 10;
	size = (WIDTH / SIZE_X) - ((e * SIZE_X) / ((WIDTH / SIZE_X) - (2 * e)));
	while (++i < SIZE_Y)
	{
		i2 = -1;
		while(++i2 < SIZE_X)
		{
			p->r = 35;
			p->v = 35;
			p->b = 35;
			ft_check_snake(i, i2, p);
			ft_draw_square(i2 * (WIDTH / SIZE_X) + (e), i * (HEIGHT / SIZE_Y) + (e), size, p);
			ft_draw_bonus(p, e);
		}
	}
}

void		ft_draw_background(t_env *p)
{
	int		i;

	i = 0;
	p->r = 40;
	p->v = 40;
	p->b = 40;
	while (i < (HEIGHT * WIDTH * 4))
	{
		(p->ret)[i] = p->b;
		(p->ret)[i + 1] = p->v;
		(p->ret)[i + 2] = p->r;
		(p->ret)[i + 3] = 0;
		i += 4;
	}
}

void		ft_draw_game_over(t_env *p)
{
	int n;
	int r;

	p->img = mlx_xpm_file_to_image(p->mlx, "gameover2.xpm", &n, &r);
	p->ret = mlx_get_data_addr(p->img, &(p->bits_per_pixel),
		&(p->size_line), &(p->endian));
}

void		ft_draw(t_env *p)
{
	if (p->game_over == 0)
	{
		ft_draw_background(p);
		ft_draw_map(p);
	}
	if (p->game_over == 1)
	{
		ft_draw_game_over(p);
	}
}