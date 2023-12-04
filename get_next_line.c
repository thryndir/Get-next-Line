/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:39:29 by lgalloux          #+#    #+#             */
/*   Updated: 2023/12/04 15:06:51 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean_line(char *buffer)
{
	size_t		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	ft_strlcpy(buffer, buffer + i, ft_strlen(buffer + i) + 1);
}

char	*ft_strchr(const char *string, int searchedChar)
{
	while (*string != '\0')
	{
		if (*string == (unsigned char)searchedChar)
			return ((char *)string);
		string++;
	}
	if (*string == (const char)searchedChar)
		return ((char *)string);
	return (NULL);
}

char	*ft_end_of_line(char *str, char *buffer)
{
	ft_clean_line(buffer);
	if (str[0])
		return (str);
	free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*str;
	ssize_t		n;

	n = BUFFER_SIZE;
	str = malloc(ft_strlen(buffer) + 1);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	ft_strlcat(str, buffer, ft_strlen(buffer) + 1);
	while (n == BUFFER_SIZE && !ft_strchr(str, '\n'))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(str);
			buffer[0] = '\0';
			return (NULL);
		}
		buffer[n] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (ft_end_of_line(str, buffer));
}

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }