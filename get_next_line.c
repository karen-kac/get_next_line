/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokono <myokono@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:40:04 by myokono           #+#    #+#             */
/*   Updated: 2023/11/17 12:35:16 by myokono          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int find_newline(const char *buffer)
{
    int i = 0;
    while (buffer[i])
    {
        if (buffer[i] == '\n')
            return i;
        i++;
    }
    return -1;
}

static char *append_line(char *line, const char *buffer, int newline_index)
{
    int line_len = 0, buffer_len = 0, i = 0;
    char *new_line;

    while (line && line[line_len])
        line_len++;
    while (buffer[i] && (newline_index < 0 || i <= newline_index))
    {
        buffer_len++;
        i++;
    }

    new_line = malloc(line_len + buffer_len + 1);
    if (!new_line)
        return NULL;
    i = -1;
    while (++i < line_len)
        new_line[i] = line[i];
    i = -1;
    while (++i < buffer_len)
        new_line[line_len + i] = buffer[i];
    new_line[line_len + buffer_len] = '\0';

    free(line);
    return new_line;
}

static int update_buffer(char **buffer, int newline_index, int read_status)
{
    //char *new_buffer;
    int i = 0, j = newline_index + 1;

    while (j < read_status)
    {
        (*buffer)[i] = (*buffer)[j];
        i++; j++;
    }
    (*buffer)[i] = '\0';

    return i;
}

static char *finalize_line(char **line, int read_status)
{
    if (read_status < 0 || (read_status == 0 && (!*line || **line == '\0')))
    {
        free(*line);
        return NULL;
    }
    return *line;
}

char *get_next_line(int fd)
{
    static char *buffer;
    char *line = NULL;
    int read_status;
    int newline_index;
    int buffer_len;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    if (!buffer)
    {
        buffer = malloc(BUFFER_SIZE + 1);
        if (!buffer)
            return (NULL);
    }

    while (1)
    {
        read_status = read(fd, buffer, BUFFER_SIZE);
        if (read_status <= 0)
        {
            free(buffer);
            return(NULL);
        }
        buffer[read_status] = '\0';
        newline_index = find_newline(buffer);
        line = append_line(line, buffer, newline_index);
        if (newline_index >= 0)
        {
            buffer_len = update_buffer(&buffer, newline_index, read_status);
            if (buffer_len <= 0)
                break;
        }
    }

    return finalize_line(&line, read_status);
}
