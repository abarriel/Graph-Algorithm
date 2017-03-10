/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarriel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 22:07:24 by abarriel          #+#    #+#             */
/*   Updated: 2017/03/06 07:51:00 by abarriel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_join(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strdup(s1);
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	return (s1);
}

static int	gnl_read(int const fd, char *tmpline, char *tmpbuf[0], char **line)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmpsub;
	int		ret;
	int		i;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		i = 0;
		buf[ret] = '\0';
		while ((buf[i] != '\n' && buf[i] != '\0') && i < BUFF_SIZE)
			i++;
		tmpsub = ft_strsub(buf, 0, i);
		tmpline = gnl_join(tmpline, tmpsub);
		*line = tmpline;
		free(tmpsub);
		if (buf[i] == '\0' && i != BUFF_SIZE)
			buf[i] = '\n';
		else if (buf[i] == '\n' && (tmpbuf[fd] = ft_strdup(&buf[i + 1])))
			return (1);
	}
	i = (tmpline[0] != '\0') ? 1 : 0;
	i = (ret < 0) ? -1 : i;
	// ft_printf("%s\n", *line);
	return (i);
}

void		normi(char **tmpbuf, char *tmp1, char *line)
{
	*tmpbuf = ft_strdup(tmp1);
	// ft_printf("%s\n", line);
}

int			get_next_line(int const fd, char **line)
{
	static char		*tmpbuf[256];
	char			*tmpl;
	char			*tmp;
	int				i;

	if (!line || fd > 256 || !(tmpl = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	*line = tmpl;
	tmp = (tmpbuf[fd] != NULL) ? ft_strdup(tmpbuf[fd]) : NULL;
	ft_bzero(tmpl, BUFF_SIZE);
	i = 0;
	while (tmp != NULL && tmp[i] != '\0')
	{
		if (tmp[i] == '\n')
		{
			normi(&tmpbuf[fd], &tmp[i + 1], *line);
			return (1);
		}
		tmpl = gnl_join(tmpl, ft_strsub(tmp, i++, 1));
		*line = tmpl;
	}
	tmpbuf[fd] = &tmp[i];
	i = gnl_read(fd, tmpl, tmpbuf, line);
	i = (tmpl[0] != '\0') ? 1 : i;
	return (i);
}
