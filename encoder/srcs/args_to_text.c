/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:50:51 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 10:47:13 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"


/**
 * It reads the arguments passed to the program and stores them in a string. If the argument is a text file, checking if the file exists and if it is readable. Concatena the text file to the string that will hold the text to be encoded.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The array of arguments passed to the program.
 * 
 * @return 1 if the arguments are valid, 0 otherwise.
 */
int	read_args(int argc, char **argv)
{
	int	i_args = 1;
	unsigned char	*text_file = NULL;
	int				size_text;

	if(argc < 2){
		printf("ERROR: Invalid number of arguments.\n");
		return(0);
	}
	enc.text = (unsigned char *)strdup("");
	while(argv[i_args])
	{
		text_file = (unsigned char *)strdup("");
		if (access(argv[i_args], F_OK | R_OK) != -1){
			size_text = count_c_txt(argv[i_args]);
			text_file = calloc (size_text + 1, sizeof(unsigned char));
			read_text(argv[i_args], text_file);
		}
		if (strlen((char*)text_file) > 0)
			enc.text = ft_strjoin(enc.text, text_file);
		else
			enc.text = ft_strjoin(enc.text, (unsigned char*)argv[i_args]);
		if (i_args < argc - 1)
			enc.text = ft_strjoin(enc.text, (unsigned char*)" ");
		free(text_file);
		i_args++;
	}
	return(1);
}

/**
 * It counts the number of characters in a text file passed as argument
 * 
 * @param argv the name of the file to be read
 * @return the number of characters in the file.
 */
int	count_c_txt(char *argv)
{
	FILE *file_txt = fopen(argv, "r");
	int	count_char = 0;

	if (file_txt == NULL)
		exit (ERROR_OPEN_FILE);
	while (fgetc(file_txt) != -1)
		count_char++;
	fclose(file_txt);
	return (count_char);
}

/**
 * It reads the text file passed as argument and stores it in an array
 * 
 * @param argv the name of the file to be read
 * @param text_file This is the array that will hold the text file.
 */
void	read_text(char *argv, unsigned char *text_file)
{
	FILE	*text = fopen(argv, "r");
	char	c;
	int		i = 0;
	
	if (text == NULL)
		exit (ERROR_OPEN_FILE);
	while (!feof(text)){
		c = fgetc(text);
		if (c != -1){
			text_file[i] = c;
			i++;
		}
	}
}
