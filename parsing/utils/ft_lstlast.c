/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 23:17:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/07/13 09:22:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

t_data	*ft_lstlast(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
