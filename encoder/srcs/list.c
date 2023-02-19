/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:59:25 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:30:38 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It initializes the list
 */
void	init_list()
{
	enc.list = calloc(1, sizeof(t_list));
	enc.list->start = NULL;
	enc.list->size = 0;
}

/**
 * It inserts a node in the list in ascending order of frequency
 * 
 * @param node the node to be inserted
 */
void	insert_sort(t_node *node)
{
	t_node	*aux;

	if (enc.list->start == NULL){
		enc.list->start = node;
	}
	else if (node->freq < enc.list->start->freq){
		node->next = enc.list->start;
		enc.list->start = node;
	}
	else {
		aux = enc.list->start;
		while (aux->next && aux->next->freq <= node->freq)
			aux = aux->next;
		node->next = aux->next;
		aux->next = node;
	}
	enc.list->size++;
}

/**
 * It removes the first node of the list and returns it
 * 
 * @return A pointer to a node.
 */
t_node	*remove_init_node()
{
	t_node	*aux = NULL;

	if (enc.list->start){
		aux = enc.list->start;
		enc.list->start = aux->next;
		aux->next = NULL;
		enc.list->size--;
	}
	return (aux);
}

/**
 * It creates a linked list of nodes, each node containing a character and its frequency
 */
void	prepare_list()
{
	printf("Making sorted frequency list...\n");
	t_node	*new;

	bzero(enc.list, sizeof(t_list));
	for (int i=0; i < 256; i++){ 
		if (enc.freq_tab[i] > 0){
			new = malloc(sizeof(t_node));
			if (new == NULL)
				exit (ERROR_MALLOC);
			new->c = i;
			new->freq = enc.freq_tab[i];
			new->r = NULL;
			new->l = NULL;
			new->next = NULL;
			insert_sort(new);
		}
	}
}
