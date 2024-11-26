/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathildelaussel <mathildelaussel@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:45:15 by mlaussel          #+#    #+#             */
/*   Updated: 2024/11/26 20:48:32 by mathildelau      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// IL FAUT LIRRE DE BUFFER_SIZE EN BUFFER_SIZE ET LE STOCKER.
// ENSUITE ON CHERCHE DANS LE STOCK SI Y A \N

char	*ft_extract_bloc(char *buffer, char *rest)
{
	int		i;
	char	*bloc;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0' && i <= BUFFER_SIZE)
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		bloc = ft_substr(buffer, 0, i);
		if (bloc == NULL)
			return (NULL);
		rest = ft_substr(buffer, i, ft_strlen(buffer) - ft_strlen(bloc));
	}
	else
	{
		
	}
	return (bloc);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	ssize_t		check_read;
	char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
		
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
		
	check_read = read(fd, buffer, BUFFER_SIZE);
	if (check_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (check_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[check_read] = '\0';
	while (buffer != '\0')
	{
		rest = ft_extract_bloc(buffer, rest);
	}
	free(buffer);
	return ();
}

/*
ssize_t version signe de size_t
ssize_t	read(int fd, void *buf, size_t count);
Paramètres :

fd : Le descripteur de fichier (file descriptor) qui
identifie la source d'entrée (obtenu, par exemple,
avec open ou des descripteurs prédéfinis comme STDIN_FILENO).
buf : Un pointeur vers un buffer (tableau) où les données lues seront stockées.
count : Le nombre maximal d'octets à lire.
Valeur de retour :

Le nombre d'octets réellement lus (peut être inférieur à count).
0 si la fin du fichier (EOF) est atteinte.
-1 en cas d'erreur, avec la variable globale errno définissant l'erreur.
*/

// substr renvoie une sous chaine en prenant
// le start d`une chaine et le nombre de commentaire
