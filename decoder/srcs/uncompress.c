/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncompress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:02:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:36:02 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

/**
 * It returns 1 if the bit at position i in byte is 1, and 0 otherwise
 * 
 * @param byte the byte to check
 * @param i the bit we want to check
 * 
 * @return The bit at position i in byte.
 */
static unsigned int	is_bit(unsigned char byte, int i)
{
	unsigned char	mask = (1 << i); // 00000001
	return (byte & mask);
}

/**
 * It takes a Huffman tree and a compressed text, and returns the uncompressed text
 * 
 * @param tree the tree that was created from the header
 * @param size_text the size of the text to be uncompressed
 * @param text_compress the compressed text
 * @param text_uncompress the text that will be uncompressed
 * 
 * @return The number of bytes read from the compressed file.
 */
int	uncompress(t_node *tree, int size_text, unsigned char* text_compress, unsigned char* text_uncompress)
{
	unsigned char	byte = 0;
	int	i, i_tc, i_tuc;
	t_node	*aux = tree;

	i_tc = 0;
	i_tuc = 0;
	while (size_text > -1){
		byte = text_compress[i_tc];
		for (i = 7; i >= 0; i--){
			aux = is_bit(byte, i) ? aux->r : aux->l ;
			if (aux->l == NULL && aux->r == NULL){
				if (size_text < 1)
					return (i_tc);
				text_uncompress[i_tuc] = aux->c;
				i_tuc++;
				aux = tree;
				size_text--;
			}
		}
		i_tc++;
	}
	return (i_tc);
}
