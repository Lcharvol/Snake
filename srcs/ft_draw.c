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

void		ft_draw_pixel(t_env *p, int y, int x)
{
	p->ret[((y * WIDTH * 4) +
		(x * 4))] = p->r;
	p->ret[1 + ((y * WIDTH * 4) +
		(x * 4))] = p->v;
	p->ret[2 + ((y * WIDTH * 4) +
		(x * 4))] = p->b;
	p->ret[3 + ((y * WIDTH * 4) +
		(x * 4))] = 0;
}

void		ft_draw_circle(t_env *p, int rayon, int centre_y, int centre_x)
{
	int y;
	int x;
	int m;

	x = 0;
	y = rayon;
	m = 5 - (4 * rayon);
	while (x <= y)
	{
		ft_draw_pixel(p, x + centre_x, y + centre_y );
        ft_draw_pixel(p, y + centre_x, x + centre_y );
        ft_draw_pixel(p, -x + centre_x, y + centre_y );
        ft_draw_pixel(p, -y + centre_x, x + centre_y );
        ft_draw_pixel(p, x + centre_x, -y + centre_y );
        ft_draw_pixel(p, y + centre_x, -x + centre_y );
        ft_draw_pixel(p, -x + centre_x, -y + centre_y );
        ft_draw_pixel(p, -y + centre_x, -x + centre_y );
        if (m > 0)
        {
        	y = y -1;
        	m = m - (8 * y) + 4;
        }
        x++;
        m = m + (8 * x) + 4;
	
	}
}
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

int			ft_check_pos_bonus(int x, int y, t_env *p)
{
	t_snake *s;
	t_wall *w;

	s = p->snake;
	w = p->wall;
	while (p->snake->next != NULL)
	{
		if (p->snake->pos_x == x && p->snake->pos_y == y)
		{
			p->snake = s;
			p->wall = w;
			return (1);
		}
		p->snake = p->snake->next;
	}
	while (p->wall->next != NULL)
	{
		if (p->wall->x == x && p->wall->y == y)
		{
			p->snake = s;
			p->wall = w;
			return (1);
		}
		p->wall = p->wall->next;
	}
	p->snake = s;
	p->wall = w;
	return (0);
}

void		ft_draw_bonus(t_env *p, int e)
{
	int size;
	int i;
	static int time = 0;

	i = ft_get_alea();
	size = (WIDTH / SIZE_X) - ((e * SIZE_X) / ((WIDTH / (SIZE_X)) - (2 * e)));
	size -= (size * 0.7);
	if (p->bonus_x == p->snake->pos_x && p->bonus_y == p->snake->pos_y)
	{
		p->bonus_x = ft_get_alea();
		p->bonus_y = ft_get_alea();
		while (ft_check_pos_bonus(p->bonus_x, p->bonus_y, p) != 0)
		{
			p->bonus_x = ft_get_alea();
			p->bonus_y = ft_get_alea();
		}
		p->snake = ft_add_snake(p, p->bonus_x, p->bonus_y);
		p->score += 1;
	}
	time++;
	if (time > 1000)
		time = 0;
	if (time %  2 == 0 && p->move == 1)
	{
		ft_choose_color(p);
	}
	else
	{
		ft_choose_color(p);
	}
	ft_draw_square((p->bonus_x * (WIDTH / SIZE_X)) + (e + size + 1), p->bonus_y * (HEIGHT / SIZE_Y) + (e + size + 1), size, p);
}

void		ft_check_wall(int i, int i2, t_env *p)
{
	t_wall *tmp;

	tmp = p->wall;
	while (p->wall->next != NULL)
	{
		if (p->wall->x == i2 && p->wall->y == i)
		{
			p->r = 255;
			p->v = 5;
			p->b = 150 +ft_get_alea();
		}
		p->wall = p->wall->next;

	}
	if (p->wall->x == i2 && p->wall->y == i)
	{
		p->r = 255;
		p->v = 5;
		p->b = 150 +ft_get_alea();
	}
	p->wall = tmp;
}

void		ft_draw_map(t_env *p)
{
	int i;
	int i2;
	int size;
	int e;

	i = -1;
	e = 0;
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
			ft_check_wall(i, i2, p);
			ft_draw_square(i2 * (WIDTH / SIZE_X) + (e), i * (HEIGHT / SIZE_Y) + (e), size, p);
			ft_draw_bonus(p, e);
		}
	}
}

void		ft_draw_background(t_env *p)
{
	int		i;

	i = 0;
	p->r = 105;
	p->v = 105;
	p->b = 105;
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
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	p->img = mlx_xpm_file_to_image(p->mlx, "gameover2.xpm", &n, &r);
	p->ret = mlx_get_data_addr(p->img, &(bits_per_pixel),
		&(size_line), &(endian));
}

void		ft_draw_score(t_env *p)
{
	char *str;

	str = "Score: ";
	mlx_string_put(p->mlx, p->win, WIDTH - 130, 10,
		0x0FFFFFF, str);
	str = ft_itoa(p->score);
	mlx_string_put(p->mlx, p->win, WIDTH - 30, 10,
		0x0FFFFFF, str);
	str = "Level: ";
	mlx_string_put(p->mlx, p->win, WIDTH - 130, 30,
		0x0FFFFFF, str);
	str = ft_itoa(p->level);
	mlx_string_put(p->mlx, p->win, WIDTH - 30, 30,
		0x0FFFFFF, str);

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