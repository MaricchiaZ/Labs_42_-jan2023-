/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   huffman_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:56:53 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:30:11 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes the two nodes with the lowest frequency, combines them into a new node, and inserts the new
 * node into the list
 */
void	prepare_huffman_tree()
{
	printf("Making Huffman tree...\n");
	t_node	*first, *second, *new;
	
	while (enc.list->size > 1){
		first = remove_init_node();
		second = remove_init_node();
		new = malloc(sizeof(t_node));
		if (new == NULL)
			exit (ERROR_MALLOC);
		new->c = '+';
		new->freq = (first->freq + second->freq);
		new->l = first;
		new->r = second;
		new->next = NULL;
		insert_sort(new);
		enc.tree = enc.list->start;
	}
}
