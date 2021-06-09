#include "get_next_line.h"
#include <stdio.h>
staticintfind_newline(char *memo)
{
    inti;

    i = 0;
    if (memo == NULL)
        return (-1);
    while (memo[i])
    {
        if (memo[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

staticintget_split(char **memo, char **line, int newline_pos)
{
    char *temp;
    intlen;

    (*memo)[newline_pos] = '\0';
    *line = ft_strdup(*memo);
    len = ft_strlen(*memo + newline_pos + 1);
    if (len == 0)
    {
        free(*memo);
        *memo = NULL;
        return (1);
    }
    temp = ft_strdup(*memo + newline_pos + 1);
    free(*memo);
    *memo = temp;
    return (1);
}

staticintcheck_memo(char **memo, char **line, int read_sz)
{
    intnewline_pos;

    if (read_sz < 0)
        return (-1);
    newline_pos = find_newline(*memo);
    if (*memo && (newline_pos >= 0))
        return (get_split(memo, line, newline_pos));
    else if (*memo)
    {
        *line = *memo;
        memo = NULL;
        return (0);
    }
    *line = ft_strdup("");
    return (0);
}

intget_next_line(int fd, char **line)
{
    static char *memo[MAX_FD];
    char *buf;
    intread_sz;
    intnewline_pos;

    if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
        return (-1);
    buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    read_sz = read(fd, buf, BUFFER_SIZE);
    while (read_sz > 0)
    {
        buf[read_sz] = '\0';
        memo[fd] = ft_strjoin(memo[fd], buf);
        newline_pos = find_newline(memo[fd]);
        if (newline_pos >= 0)
            return (get_split(&memo[fd], line, newline_pos));
        read_sz = read(fd, buf, BUFFER_SIZE);
    }
    free(buf);
    buf = NULL;
    return (check_memo(&memo[fd], line, read_sz));
}