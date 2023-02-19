/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:18:20 by maclara-          #+#    #+#             */
/*   Updated: 2023/01/15 01:38:59 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

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
		printf("ERROR: Failure to find file for shared memory");
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
		printf("ERROR: Failed creating shared memory");
		exit (ERROR_IPC);
	}
	t_shm	*sh_tree = (t_shm *) shmat(mem_block_id, NULL, 0);
	if (sh_tree == NULL){
		printf("ERROR: Failure to attach memory");
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
 * It destroys the shared memory block with the given file name
 * 
 * @param file the name of the file that will be used to create the shared memory block.
 * 
 * @return A boolean value.
 */
bool	destroy_mem(char *file)
{
	int	shared_block_id = get_id_mem_block(file, 0);
	if (shared_block_id == ERROR_IPC)
		return NULL;
	return (shmctl(shared_block_id, IPC_RMID, NULL) != ERROR_IPC);
}

/**
 * It deserializes a tree.
 * 
 * @param arr an array of long integers
 * @param index the index of the array where the next node will be read from
 * 
 * @return The root of the tree.
 */
t_node	*deserialize_tree(long int *arr, int *index)
{
	if (arr[(*index)] == -1){
		(*index)++;
		return NULL;
	}
	t_node *root = (t_node *) malloc(sizeof(t_node));
	root->c = arr[(*index)++];
	root->l = deserialize_tree(arr, index);
	root->r = deserialize_tree(arr, index);
	root->next = deserialize_tree(arr, index);
	return (root);
}
