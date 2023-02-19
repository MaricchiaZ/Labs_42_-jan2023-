/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:43:37 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:29:50 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It returns the size of the encoded string.
 * 
 * @return The size of the string that will be coded.
 */
static int	get_size_strcoded()
{
	int	i, size;

	size = 0;
	for (i = 0; enc.text[i]; i++)
		size += strlen(enc.dictionary[(int)enc.text[i]]);
	return (size);
}

/**
 * It gets the size of the coded string, allocates memory for it, and then encodes the text
 */
void	prepare_encode()
{
	printf("Encoding text...\n");
	int		size_coded;

	size_coded = get_size_strcoded();
	enc.coded = calloc((size_coded + 1), sizeof(char));
	for (int i=0; enc.text[i] != '\0'; i++)
		strcat(enc.coded, enc.dictionary[(int)enc.text[i]]);
}
