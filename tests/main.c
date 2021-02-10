/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 00:29:09 by lmartin           #+#    #+#             */
/*   Updated: 2021/02/10 10:11:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*pt;

	i = 0;
	while (s1[i])
		i++;
	if (!(pt = malloc((i + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (s1[++i])
		pt[i] = s1[i];
	pt[i] = '\0';
	return (pt);
}

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int		main(void)
{
	char *addr1;
	char *addr3;

    addr1 = (char*)malloc(16*M);
    strcpy(addr1, "Bonjour\n");
    print(addr1);
	show_alloc_mem();
    addr3 = (char*)realloc(addr1, 128*M);
	ft_putnbr(100*M);
	addr3[127*M] = 42;
    print(addr3);
	show_alloc_mem();
//    print(addr3);
    return (0);
	/*
	int		i;
	char	*tiny[5];
	
	i = -1;
	while (++i < 5)
		tiny[i] = ft_strdup("salut\n");
	show_alloc_mem();
	i = -1;
	while (++i < 5)
		write(STDOUT_FILENO, tiny[i], ft_strlen(tiny[i]));
	tiny[0] = realloc(tiny[0], 30);
	tiny[1] = realloc(tiny[1], 7);
	tiny[2] = realloc(tiny[2], 3);
	tiny[2][2] = '\0';
	show_alloc_mem();
	i = -1;
	while (++i < 5)
		write(STDOUT_FILENO, tiny[i], ft_strlen(tiny[i]));
	return (0);
	*/
}
