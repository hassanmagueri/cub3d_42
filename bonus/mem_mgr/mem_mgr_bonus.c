/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgr_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:46:14 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/24 16:35:05 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

typedef struct s_mem_mgr
{
    void *address;
    struct s_mem_mgr *next;
} t_free;
void ft_free(t_free *head)
{
    t_free *temp;

    while (head)
    {
        temp = head;
        head = head->next;
        free(temp->address);
        free(temp);
    }
    
}
t_free *create_new_node(void *address)
{
    t_free *new;
    new = (t_free *)malloc(sizeof(t_free));
    if (!new)
        return (NULL);
    new->address = address;
    new->next = NULL;
    return (new);
}

void add_back(t_free **list, t_free *new)
{
    t_free *temp;

    if (!*list)
    {
        *list = new;
        return;
    }
    temp = *list;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
}

void *ft_malloc(size_t size, int status)
{
    static t_free *head = NULL;
    t_free *new_node;

    t_free *new;
    if (status == ALLOC)
    {
        new = malloc(size);
        if (!new)
            return (NULL);
        new_node = create_new_node(new);
        
        add_back(&head, new_node);
        return (new);
    }
    else if (status == FREE)
    {
        ft_free(head);
        head = NULL;
    }
    return (NULL);
}