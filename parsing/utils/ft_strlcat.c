/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:16:24 by belguabd          #+#    #+#             */
/*   Updated: 2024/07/10 16:22:27 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../parse.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	len_cpy;

	if (!dstsize && !dst)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	len_cpy = dstsize - dest_len - 1;
	i = 0;
	while (i < len_cpy && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
