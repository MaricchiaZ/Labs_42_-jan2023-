/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:27:52 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 02:38:50 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "decoder.h"

/**
 * The above function is the main function of the decoder. It attaches the shared memory block,
 * deserializes the tree, uncompresses the text and writes the uncompressed text in the shared memory.
 * 
 * @return The number of bytes of the uncompressed text.
 */
int	main()
{
	int			i = 0;
	long int	initial_time;
	long int	final_time;
	
	setlocale(LC_ALL, "C.UTF-8");
	t_shm	*block = attach_mem_block("README.md", sizeof(t_shm));
	if (!block){
		printf("ERROR: Failure reading shared memory\n");
		exit (ERROR_SHMEM);
	}
	t_node	*tree = deserialize_tree(block->tree_serialize, &i);
	printf("Decoded....\n");
	initial_time = get_time();
	block->bytes_compress_text = uncompress(tree, block->text_size, block->compressed_text, block->uncompressed_text);
	block->text_size = strlen((char *)block->uncompressed_text);
	final_time = get_time();
	block->time_to_decode = final_time - initial_time;
	printf("Sharing operation data with encoder ....\n");
	detach_mem(block);
	printf(ANSI_GREEN "\tUncompressed text ready in the shared memory\n" RESET_COLOR);
	printf("(Look at the return in the ./encoder program)\n");
	freeTree(tree);
	return (0);
}
