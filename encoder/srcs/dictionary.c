/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:10:58 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 10:11:03 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * Its count height ot tree, and return the maximum of the height of the left and right
 * subtrees plus one. If the root is NULL, return -1.
 * 
 * @param root the root of the tree
 * 
 * @return The height of the tree.
 */
static int	height_tree(t_node *root)
{
	int	l, r; 

	if (root == NULL)
		return (-1);
	else{
		l = height_tree(root->l) + 1;
		r = height_tree(root->r) + 1;
	}
	return (l > r) ? l : r;
}

/**
 * It allocates memory for the dictionary. Creating the matrix dictionary with the size of ASCII thus optimizes program execution, because we have a direct access, by the ASCII value of the character.
 * 
 * @return A pointer to a pointer to a char.
 */
static char	**malloc_dic()
{
	char	**dictionary;
	int		i;
	
	dictionary = malloc(sizeof(char *) * 256);
	for (i = 0; i < 256; i++){
		dictionary[i] = calloc((enc.col + i), sizeof(char));
	}
	return(dictionary);
}

/**
 * It takes a dictionary, a root node, a code_c, and a column number as parameters. It then creates two
 * strings, l and r, and copies the code_c into them. It then concatenates a 0 to l and a 1 to r. If
 * the root node is a leaf node, it copies the code_c into the dictionary at the index of the root
 * node's character. If the root node is not a leaf node, it recursively calls itself on the left and
 * right nodes of the root node, passing in the dictionary, the left and right nodes, and the l and r
 * strings
 * 
 * @param dictionary the dictionary we're building
 * @param root the root of the tree
 * @param code_c the code for the current node
 * @param col the length of the longest code in the dictionary
 */
void	make_dictionary(char ** dictionary, t_node *root, char *code_c, int col)
{
	char l[col], r[col];
	if (root->l == NULL && root->r == NULL)
		strcpy(dictionary[root->c], code_c);
	else{
		strcpy(l, code_c);
		strcpy(r, code_c);

		strcat(l, "0");
		strcat(r, "1"); 
		make_dictionary(dictionary, root->l, l, col);
		make_dictionary(dictionary, root->r, r, col);
	}
}

/**
 * It takes the tree height and makes a dictionary out of it
 */
void	prepare_dictionary()
{
	printf("Making dictionary...\n");
	enc.col = height_tree(enc.tree);
	enc.dictionary = malloc_dic();
	make_dictionary(enc.dictionary, enc.tree, "", enc.col);
}
