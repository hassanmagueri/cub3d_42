/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:17:56 by belguabd          #+#    #+#             */
/*   Updated: 2024/08/26 14:32:55 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_data	*ft_lstnew(void *content)
{
	t_data	*newstr;

	newstr = (t_data *)ft_malloc(sizeof(t_data) );
	if (!newstr)
		return (NULL);
	newstr->content = content;
	newstr->next = NULL;
	return (newstr);
}
