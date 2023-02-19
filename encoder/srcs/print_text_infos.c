/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:44:09 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:31:02 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It prints the decoded text, the original text size, the encoded text size, the decoded text size,
 * the compression percentage, and the time it took to decode the text
 * 
 * @param block pointer to the shared memory block
 */
void	print_infos(t_shm *block)
{
	printf("Finish!!!\n\n");
	printf("Text decoded:\n");
	printf("%s\n", block->uncompressed_text);
	printf("\n");
	printf("   _____________________________________________________\n\n");
	printf("\toriginal text size: \t%d bytes\n", enc.text_size);
	printf("\tencoded text size: \t%d bytes\n", block->bytes_compress_text);
	printf("\tdecoded text size \t%d bytes\n", block->text_size);
	printf("\tcompression to \t\t%.2f %% of original\n", ((float)(block->bytes_compress_text * 100)/enc.text_size));
	printf("\ttime to decoder \t%d ms\n", block->time_to_decode);
	printf("   _____________________________________________________\n\n");
}
