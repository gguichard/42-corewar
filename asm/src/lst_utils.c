/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 04:07:07 by wta               #+#    #+#             */
/*   Updated: 2019/02/18 04:28:08 by rvalenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "asm.h"

void	lst_pushback(t_list_ref *list, t_list *node)
{
	if (list != NULL && node != NULL)
	{
		if (list->head == NULL)
		{
			list->head = node;
			list->tail = node;
		}
		else
		{
			list->tail->next = node;
			list->tail = node;
		}
	}
}

t_list	*lstnew_mallocfree(void *content)
{
	t_list	*elem;

	if ((elem = (void*)malloc(sizeof(t_list))) != NULL)
	{
		elem->next = NULL;
		elem->content = content;
		elem->content_size = sizeof(content);
	}
	return (elem);
}

void	lst_free(t_list_ref *list)
{
	t_list	*ref;

	ref = list->head;
	while (ref != NULL)
	{
		ref = ref->next;
		free(list->head);
		list->head = ref;
	}
}
