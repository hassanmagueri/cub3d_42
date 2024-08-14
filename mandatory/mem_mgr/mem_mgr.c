/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:46:14 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/13 12:35:52 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_mem_mgr
{
    void *address;
    struct s_mem_mgr *next;
} t_free;

t_free *add_new_node(void *address)
{
    t_free *new;
    new = (t_free *)ft_malloc(sizeof(t_free), ALLOC);
    if (!new)
        return (NULL);
    new->address = address;
    new->next = NULL;
    return (new);
}

void add_back(t_free **list, t_free *new)
{
    if (*list)
    {
        *list = new;
        return;
    }
    while ((*list)->next)
        *list = (*list)->next;
    *list = new;
}

void *ft_malloc(size_t size, int status)
{
    static t_free *head;
    t_free *new;
    if (status == ALLOC)
    {
        new = malloc(size);
        if (!new)
            return (NULL);
        add_back(&head, add_new_node(new));
        return (new);
    }
    return (NULL);
}