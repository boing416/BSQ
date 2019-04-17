/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurkass <mnurkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:23:09 by mnurkass          #+#    #+#             */
/*   Updated: 2019/04/16 18:27:22 by mnurkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h> 
# include <stdlib.h>
# include <stdio.h>   
# include <string.h>

# define BUF_SIZE 4096

char OB;
char X;
int COL_COUNT;
int LINE_COUNT; 
int LENGTH; 

typedef struct s_rectangle 
{
    int start_row;
    int end_row;
    int left_col;
    int right_col;
    int rec_area;  
}               t_rectangle;


/* LIBRARY */
void	ft_putstr(char *str);
void	ft_putchar(char c);
void	ft_putnbr(int nbr); 
int     ft_atoi(char *src);

/* PROGRAMM FUNCTIONS */
void parse_map(char **av);  
void read_map(register int *const fd);
void get_params(register int *const fd);
void draw_map(register int *const fd);
void check_length(int s1, int s2);
t_rectangle get_map(register int *const fd);
t_rectangle get_map2(register int *const fd);
void show_map(register int *const fd,t_rectangle rectangle);

#endif
