/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcharvol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 05:46:05 by lcharvol          #+#    #+#             */
/*   Updated: 2017/03/08 05:46:06 by lcharvol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/snake.h"

void		ft_start_env(t_env **p)
{
	t_snake *new;

	(*p)->snake = (t_snake *)malloc(sizeof(t_snake));
	(*p)->wall = (t_wall *)malloc(sizeof(t_wall));
	(*p)->bonus_x = ft_get_alea();
	(*p)->bonus_y = ft_get_alea();
	(*p)->r = 0;
	(*p)->v = 0;
	(*p)->b = 0;
	(*p)->pos_x = 5;
	(*p)->pos_y = 5;
	(*p)->snake->pos_x = 5;
	(*p)->snake->pos_y = 5;
	(*p)->snake->id = 1;
	(*p)->snake->dir = 1;
	(*p)->snake->next = NULL;
	(*p)->snake->prev = NULL;
	(*p)->game_over = 0;
	(*p)->score = 1;
	(*p)->move = 0;
	(*p)->wall->x = -1;
	(*p)->wall->y = -1;
	(*p)->wall->next = NULL;
	(*p)->wall->prev = NULL;
	(*p)->level = 1;
}

void	ft_verif(t_env *p)
{
	t_snake *tmp;
	int i;

	i = 1;
	tmp = p->snake;
	while (p->snake->next != NULL)
	{
		printf("Id[%d]: %d\n", i, p->snake->id);
		printf("Id[%d]: positon_x %d\n", i, p->snake->pos_x);
		printf("Id[%d]: positon_y %d\n", i, p->snake->pos_y);
		p->snake = p->snake->next;
		i++;
	}
	printf("Id[%d]: %d\n", i, p->snake->id);
	printf("Id[%d]: positon_x %d\n", i, p->snake->pos_x);
	printf("Id[%d]: positon_y %d\n", i, p->snake->pos_y);
	printf("sortie\n");
	p->snake = tmp;
}

void		ft_game_over(t_env *p)
{
	p->game_over = 1;
}

void		ft_move_snake(t_env *p)
{
	t_snake *new;

	new = p->snake;
	while(p->snake->next != NULL)
	{
		if (p->snake->prev == NULL)
		{
			if (p->snake->dir == 3)
			{
				if ((p->snake->pos_x + 1) < SIZE_X)
					p->snake->pos_x += 1;
				else
					p->snake->pos_x = 0;
			}
			if (p->snake->dir == 4)
			{
				if ((p->snake->pos_x - 1) >= 0)
					p->snake->pos_x -= 1;
				else
					p->snake->pos_x = SIZE_X - 1;
			}
			if (p->snake->dir == 2)
			{
				if ((p->snake->pos_y + 1) < SIZE_Y)
					p->snake->pos_y += 1;
				else
					p->snake->pos_y = 0;
			}
			if (p->snake->dir == 1)
			{
				if ((p->snake->pos_y - 1) >= 0)
					p->snake->pos_y -= 1;
				else
					p->snake->pos_y = SIZE_Y - 1;
			}
		}
		p->snake = p->snake->next;
	}
	while (p->snake->prev != NULL)
	{
		p->snake->pos_x = p->snake->prev->pos_x;
		p->snake->pos_y = p->snake->prev->pos_y;
		p->snake = p->snake->prev;
	}
	p->snake = new;
}

t_wall		*ft_add_wall(t_env *p)
{
	t_wall *new;
	t_wall *init;

	init = p->wall;
	new = (t_wall *)malloc(sizeof(t_wall));
	new->next = NULL;
	new->x = ft_get_alea();
	new->y = ft_get_alea();
	while (p->wall->next != NULL)
	{
		p->wall = p->wall->next;
	}
	p->wall->next = new;
	new->next = NULL;
	p->wall = init;
	return (p->wall);
}

void		ft_move(t_env *p)
{
	static int tmp = 3;

	ft_move_snake(p);
	ft_verif_coli(p);
	ft_verif_wall(p);
	if ((p->score % tmp) == 0)
	{
		p->wall = ft_add_wall(p);
		tmp += 3;
	}
	p->move = 0;
}

static int	ft_loop_key_hook(t_env *p)
{
	char	*str;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	static int time = 0;
	static	int 	tmp = 0;

	time++;
	if (time > 1000)
		time = 0;
	if ((time % (7 - p->level))== 0)
		ft_move(p);
	if (p->score % 21 == 0)
		tmp = 0;
	if (p->score % 20 == 0 && tmp == 0)
	{
		p->level += 1;
		tmp = 1;
	}
	p->ret = mlx_get_data_addr(p->img, &(bits_per_pixel),
	&(size_line), &(endian));
	ft_draw(p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
	mlx_destroy_image(p->mlx, p->img);
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	ft_draw_score(p);
	return (0);
}

int			ft_key_hook(int keycode, t_env *p)
{
	if (keycode == ECHAP)
		exit(1);
	if (keycode == UP && p->snake->dir != 2 && p->move == 0)
	{
		p->snake->dir = 1;
		p->move = 1;
	}
	if (keycode == DOWN && p->snake->dir != 1 && p->move == 0)
	{
		p->snake->dir = 2;
		p->move = 1;
	}
	if (keycode == LEFT && p->snake->dir != 4 && p->move == 0)
	{
		p->snake->dir = 3;
		p->move = 1;
	}
	if (keycode == RIGHT && p->snake->dir != 3 && p->move == 0)
	{
		p->snake->dir = 4;
		p->move = 1;
	}
	return (0);
}

int			ft_mouse_hook(int button, int x, int y, t_env *p)
{
	if (button == 1)
	{
		p->game_over = 0;
	}
	return (0);
}

int 		get_pos_x(int dir, int x)
{
	if (dir == 1 || dir == 2)
		return (x);
	if (dir == 3)
		return (x - 1);
	if (dir == 4)
		return (x + 1);
	return (0);
}

int 		get_pos_y(int dir, int y)
{
	if (dir == 3 || dir == 4)
		return (y);
	if (dir == 1)
		return (y + 1);
	if (dir == 2)
		return (y - 1);
	return (0);
}

t_snake		*ft_add_snake(t_env *p, int x, int y)
{
	t_snake *new;
	t_snake *init;

	init = p->snake;
	new = (t_snake *)malloc(sizeof(t_snake));
	new->next = NULL;
	new->pos_x = get_pos_x(p->snake->dir, p->snake->pos_x);
	new->pos_y = get_pos_y(p->snake->dir, p->snake->pos_y);
	while (p->snake->next != NULL)
	{
		p->snake = p->snake->next;
	}
	new->id = p->snake->id + 1;
	p->snake->next = new;
	new->prev = p->snake;
	new->dir = p->snake->dir;
	new->next = NULL;
	p->snake = init;
	return (p->snake);
}


int	main(void)
{

	t_env	*p;

	p = (t_env *)malloc(sizeof(t_env));
	ft_start_env(&p);
	ft_add_snake(p, 0 , 0);
	ft_add_snake(p, 1 , 1);
	ft_add_snake(p, 2 , 2);
	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "Snake");
	p->img = mlx_new_image(p->mlx, WIDTH, HEIGHT);
	mlx_hook(p->win, 2, 2, ft_key_hook, p);
	mlx_mouse_hook(p->win, ft_mouse_hook, p);
	ft_loop_key_hook(p);
	mlx_loop_hook(p->mlx, ft_loop_key_hook, p);
	mlx_loop(p->mlx);
	free(p);
	return (0);
}
