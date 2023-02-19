/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frequency_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 08:31:11 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 10:10:22 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It creates a frequency table for the characters in the text. Creating the table with the size of ASCII thus optimizes program execution, because we have a direct access table, by the ASCII value of the character.
 * 
 */
void	prepare_freq_table()
{
	unsigned int	aux;
	
	printf("Making the frequency table...\n");
	enc.freq_tab = (unsigned int *) calloc(256, sizeof(int));
	for(int i=0; enc.text[i] != '\0'; i++){
		aux = enc.text[i];
		enc.freq_tab[aux]++;
	}
}
