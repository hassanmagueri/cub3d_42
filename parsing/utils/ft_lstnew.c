/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:17:56 by belguabd          #+#    #+#             */
/*   Updated: 2024/07/13 09:24:00 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_data	*ft_lstnew(void *content)
{
	t_data	*newstr;

	newstr = (t_data *)malloc(sizeof(t_data));
	if (!newstr)
		return (NULL);
	newstr->content = content;
	newstr->next = NULL;
	return (newstr);
}
