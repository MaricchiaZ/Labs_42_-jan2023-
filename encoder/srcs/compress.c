/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:47:06 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 10:14:13 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes the coded text and converts it into a compressed text. Checking if the current bit is 1, If it is, it is shifting the mask to the left by j bits and then ORing it with the byte.
 * 
 */
void	compress()
{
	printf("Compressing the data...");
	unsigned char	mask, byte = 0;
	int	j = 7;
	int	i_ct = 0;

	enc.compressed_text = (unsigned char *)calloc(enc.text_size + 1, sizeof(char));
	for (int i = 0; enc.coded[i]; i++){
		mask = 1;
		if (enc.coded[i] == '1'){
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0){ // one byte completed
			enc.compressed_text[i_ct] = byte;
			i_ct++;
			byte = 0;
			j = 7;
		}
	}
	if (j != 7){ // the last byte incompleted
		enc.compressed_text[i_ct] = byte;
		i_ct++;
	}
	enc.size_compress_text= i_ct;
}
