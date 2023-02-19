/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:31:19 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/14 20:59:04 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

t_enc	enc;

int	main(int argc, char **argv)
{
	setlocale(LC_ALL, "C.UTF-8");
	if (!read_args(argc, argv))
		return (-1);
	enc.text_size = ft_strlen(enc.text);
	printf("\n\tStarting Huffman algorithm\n");
	init_list();
	prepare_freq_table();
	prepare_list();
	prepare_huffman_tree();
	prepare_dictionary();
	prepare_encode();
	compress();
	printf(ANSI_GREEN "\n\tCompressed text ready in the shared memory\n\n" RESET_COLOR);
	prepare_shared_memory();
	free_struct();
	return (0);
}
