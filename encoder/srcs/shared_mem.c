/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:18:20 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 02:38:29 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "encoder.h"

/**
 * It takes a file name and a size of a structure and returns a shared memory id
 * 
 * @param file The file that will be used to generate the key.
 * @param size_struct The size of the structure you want to store in the shared memory.
 * 
 * @return The id of the shared memory block
 */
static int get_id_mem_block(char *file, int	size_struct)
{
	key_t key_tree;
	key_tree = ftok(file, 42);
	if (key_tree == ERROR_IPC){
		printf("ERROR: Failure to find file for shared memory\n");
		return(ERROR_IPC);
	}
	return (shmget(key_tree, size_struct, 0644 | IPC_CREAT));
}

/**
 * This function attaches the shared memory block to the process
 * 
 * @param file The name of the file that will be used to create the shared memory.
 * @param size_struct The size of the structure that will be stored in the shared memory.
 * 
 * @return A pointer to a shared memory block.
 */
t_shm	*attach_mem_block(char *file, int size_struct)
{
	int	mem_block_id = get_id_mem_block(file, size_struct);
	if (mem_block_id == ERROR_IPC){
		printf("ERROR: Failed creating shared memory\n");
		exit (ERROR_IPC);
	}
	t_shm	*sh_tree = (t_shm *) shmat(mem_block_id, NULL, 0);
	if (sh_tree == NULL){
		printf("ERROR: Failure to attach memory\n");
		exit (ERROR_SHMAT);
	}
	return (sh_tree);
}

/**
 * Detach_mem() detaches the shared memory block from the process
 * 
 * @param block The address of the shared memory block.
 * 
 * @return A boolean value.
 */
bool	detach_mem(t_shm *block)
{
	return (shmdt(block) != ERROR_IPC);
}

/**
 * It destroys the shared memory block.
 * 
 * @param file the name of the file to be used as the key for the shared memory block.
 * 
 * @return The return value is a pointer to the shared memory block.
 */
bool	destroy_mem(char *file)
{
	int	shared_block_id = get_id_mem_block(file, 0);
	if (shared_block_id == ERROR_IPC)
		return NULL;
	return (shmctl(shared_block_id, IPC_RMID, NULL) != ERROR_IPC);
}

/**
 * It takes a tree and turns it into an array
 * 
 * @param root the root of the tree
 * @param arr the array that will be used to store the serialized tree
 * @param index the index of the array where the next element will be inserted
 * 
 * @return The array of long ints.
 */
void	serialize_tree(t_node *root, long int *arr, int *index)
{
	if (root == NULL){
		arr[(*index)++] = -1;
		return ;
	}
	arr[(*index)++] = root->c; // recebe o caracter do 1o nó
	serialize_tree(root->l, arr, index);
	serialize_tree(root->r, arr, index);
	serialize_tree(root->next, arr, index);
}

/**
 * It creates a shared memory block, serializes the tree, writes the compressed text and the size of
 * the compressed text, and then waits for the decoder to read the data and write the time it took to
 * decode the text
 */
void prepare_shared_memory()
{
	t_shm	*block = attach_mem_block("README.md", sizeof(t_shm));
	int i = 0;

	bzero(block, sizeof(t_shm));
	serialize_tree(enc.list->start, block->tree_serialize, &i);
	block->time_to_decode = -1;
	block->text_size = enc.text_size;
	block->bytes_compress_text = enc.size_compress_text;
	block->tree_size = enc.col;
	for(int j=0; j < enc.size_compress_text; j++ )
		block->compressed_text[j] = enc.compressed_text[j];
	printf("Waiting for decoder action to count time.... (rund ./decoder)\n");
	while (block->time_to_decode == -1); // espera as operações do programa decoder ocorrerem para continuar.....
	print_infos(block);
	detach_mem(block);
	destroy_mem("README.md");
}
