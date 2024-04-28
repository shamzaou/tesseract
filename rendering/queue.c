/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamzaou <shamzaou@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:28:00 by shamzaou          #+#    #+#             */
/*   Updated: 2024/04/28 19:28:00 by shamzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_queue(t_queue *q)
{
	q->front = NULL;
	q->rear = NULL;
}

void	enqueue(t_queue *q, void *val)
{
	t_queue_node	*new_node;

	new_node = (t_queue_node *)malloc(sizeof(t_queue_node));
	if (!new_node)
		return ;
	new_node->val = val;
	new_node->next = NULL;
	if (!q->front)
	{
		q->front = new_node;
		q->rear = new_node;
	}
	else
	{
		q->rear->next = new_node;
		q->rear = new_node;
	}
}

void	*dequeue(t_queue *q)
{
	t_queue_node	*tmp;
	void			*val;

	if (!q->front)
		return (NULL);
	tmp = q->front;
	val = tmp->val;
	q->front = q->front->next;
	free(tmp);
	return (val);
}

char	*queue_to_str(t_queue *q)
{
	int				len;
	char			*str;
	char			*line;
	t_queue_node	*tmp;

	len = 0;
	tmp = q->front;
	while (tmp)
	{
		len += ft_strlen(tmp->val);
		tmp = tmp->next;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	while (q->front)
	{
		line = dequeue(q);
		ft_strlcat(str, line, len + 1);
		free(line);
	}
	return (str);
}

void	free_queue(t_queue *q)
{
	t_queue_node	*tmp;

	if (!q)
		return ;
	while (q->front)
	{
		tmp = q->front;
		q->front = q->front->next;
		ft_free((void **)&(tmp->val));
		ft_free((void **)&tmp);
	}
}
