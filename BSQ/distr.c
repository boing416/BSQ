/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurkass <mnurkass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:08:48 by mnurkass          #+#    #+#             */
/*   Updated: 2019/04/16 18:27:13 by mnurkass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h" 

void parse_map(char **av)
{
    int					fd;
    t_rectangle rec;

    fd = open(av[1], O_RDONLY, 0644);
	if (fd != -1)
		get_params(&fd);
    close(fd);

    fd = open(av[1], O_RDONLY, 0644);
	if (fd != -1)        
        read_map(&fd);
    close(fd); 

    fd = open(av[1], O_RDONLY, 0644);
    if (fd != -1)        
        draw_map(&fd); 
    close(fd);  

    fd = open(av[1], O_RDONLY, 0644);
    if (fd != -1)        
        rec = get_map(&fd); 
    close(fd);  

    fd = open(av[1], O_RDONLY, 0644);
    if (fd != -1)        
        show_map(&fd, rec); 
    close(fd);    

    fd = open(av[1], O_RDONLY, 0644);
    if (fd != -1)        
        rec = get_map2(&fd);  
    close(fd);  

    fd = open(av[1], O_RDONLY, 0644);
    if (fd != -1)        
        show_map(&fd, rec); 
    close(fd);              
}

void get_params(register int *const fd)
{
    int ret;
	char buf[1 + 1];
    int wight;
    int line_count;

    wight = 0;
    line_count = 0;
    while ((ret = read(*fd, buf, 1))) 
	{        
		buf[ret] = '\0'; 
		if(wight == 3)
            OB = buf[0];
        else if(wight == 4)
            X = buf[0];
        else if(wight == 0 || wight == 1)
        {
            line_count = (line_count * 10) + ((int)buf[0] - 48);            
        }  
        wight++;
	}
    LINE_COUNT = line_count;
    COL_COUNT = (wight - 1) / line_count;
    
}

void read_map(register int *const fd)   
{
    int ret;
	char buf[BUF_SIZE + 1];
    int wight; 

    wight = 0;  
        
    while ((ret = read(*fd, buf, BUF_SIZE))) 
	{
        wight++;
		buf[ret] = '\0'; 
		ft_putstr(buf);   
	}
}

void check_length(int s1, int s2)
{
    if((s2 - s1) > LENGTH)
        LENGTH = s2 - s1;
}

void draw_map(register int *const fd)   
{
    int ret;
	char buf[1+1];
    int row;
    int col;
    int n;
    char s;
    t_rectangle rectangle;

    int s1;
    int s2;

    int rec_hight;
    int rec_width; 
    
    //int j;

    LENGTH = 0;
    
    s1 = 0;
    s2 = 0;

    row = 1;
    col = 0;  
    printf("OB: %c\t\n", OB); 
    printf("X: %c\t\n", X);
    printf("LINES: %d\t\n", LINE_COUNT);
    printf("COLS: %d\t\n", COL_COUNT);
    n = 1;

    rec_width = COL_COUNT;
    rec_hight = 1;

    rectangle.start_row = 1;
    rectangle.end_row = 0;
    rectangle.left_col = 0;
    rectangle.right_col = 0;

    printf("\n****************SEARCH RECTANGLE******************\n");
    while ((ret = read(*fd, buf, 1)))  
	{
        
        s = buf[0];
        buf[ret] = '\0';
        if(s == '\n') 
        {
            col = 0;
            row++;
           // printf("\n");
        }
        col++;
        if(row == 1)
        {
            continue;            
        }
        if(buf[0] == OB) 
        {
            printf("OB: ROW: %d, COL: %d\t\n", (row - 1), (col - 1));
        }
        if(buf[0] == OB) 
        {            
            if(rectangle.left_col != 0 && (col - 1) > rectangle.left_col && 
                (rectangle.right_col != 0) && (rectangle.right_col > (col - 1)))
            {
                rectangle.end_row = (col - 1);
                break;
            }
            if(rectangle.left_col == 0 || (col - 1) < rectangle.left_col)
                rectangle.left_col = (col - 1);
            else if(rectangle.right_col == 0)
                rectangle.right_col = (col - 1);
            // if(s1 == 0)
            //     s1 = col - 1;
            // else if(s2 == 0)
            //     s2 = col - 1;
            // check_length(s1,s2);                       
           // printf("o");
        }
        else if(buf[0] == '.')
        {
           // printf("."); 
        }               
				
	}  
    rectangle.rec_area = (rectangle.end_row - rectangle.start_row) * (rectangle.right_col - rectangle.left_col); 
    
    printf("\n*********RECTANGLE*********\n");
    printf("REC START ROW:\t%d\n", rectangle.start_row);  
    printf("REC END ROW:\t%d\n", rectangle.end_row);  
    printf("REC LEFT COL:\t%d\n", rectangle.left_col);  
    printf("REC RIGHT COL:\t%d\n", rectangle.right_col);  
    printf("REC AREA:\t%d\n", rectangle.rec_area);  
    
   
    printf("LENGTH: %d\n", LENGTH);  
}

t_rectangle get_map(register int *const fd)   
{
    int ret;
	char buf[1+1];
    int row;
    int col;
    int n;
    char s;
    t_rectangle rectangle;

    int s1;
    int s2;

    int rec_hight;
    int rec_width;
    
    //int j;

    LENGTH = 0;
    
    s1 = 0;
    s2 = 0;

    row = 1;
    col = 0;      
    n = 1;

    rec_width = COL_COUNT;
    rec_hight = 1;

    rectangle.start_row = 1;
    rectangle.end_row = 0;
    rectangle.left_col = 0;
    rectangle.right_col = 0;

    
    while ((ret = read(*fd, buf, 1)))  
	{
        
        s = buf[0];
        buf[ret] = '\0';
        if(s == '\n') 
        {
            col = 0;
            row++;
           // printf("\n");
        }
        col++;
        if(row == 1)
        {
            continue;            
        }
        if(buf[0] == OB) 
        {
            
            if(rectangle.left_col != 0 && (col - 1) > rectangle.left_col && 
                (rectangle.right_col != 0) && (rectangle.right_col > (col - 1)))
            {
                rectangle.end_row = (col - 1);
                break;
            }
            if(rectangle.left_col == 0 || (col - 1) < rectangle.left_col)
                rectangle.left_col = (col - 1);
            else if(rectangle.right_col == 0)
                rectangle.right_col = (col - 1);
            
        }                   
				
	}  
    rectangle.rec_area = (rectangle.end_row - rectangle.start_row) * (rectangle.right_col - rectangle.left_col); 
    
    return (rectangle);
}

void show_map(register int *const fd,t_rectangle rectangle)
{
    int ret;
	char buf[1+1];
    int row;
    int col;
    int n; 
    char s;
    int rec_area;
    

    int s1;
    int s2;

    int rec_hight;
    int rec_width;
    
    //int j;

    LENGTH = 0;
    rec_area = rectangle.rec_area + 1;
    
    s1 = 0;
    s2 = 0;

    row = 1;
    col = 0;  
    // printf("OB: %c\t\n", OB); 
    // printf("X: %c\t\n", X);
    // printf("LINES: %d\t\n", LINE_COUNT);
    // printf("COLS: %d\t\n", COL_COUNT);
    n = 1;

    rec_width = COL_COUNT;
    rec_hight = 1;
    
    // OB: ROW: 2, COL: 5
    // OB: ROW: 3, COL: 13
    // OB: ROW: 5, COL: 5
    // OB: ROW: 6, COL: 16
    // OB: ROW: 8, COL: 7
    // REC START ROW:	1
    // REC END ROW:	7
    // REC LEFT COL:	5
    // REC RIGHT COL:	13

    printf("\n****************DRAW RECTANGLE******************\n");
    while ((ret = read(*fd, buf, 1)))  
	{
        
        s = buf[0];
        buf[ret] = '\0';
        if(s == '\n') 
        {
            col = 0;
            row++;
            printf("\n");
        }
        col++;
        if(row == 1)
        {
            continue;            
        }
        
        if(buf[0] == OB) 
        {                 
            printf("o");
        }
        else if(buf[0] == '.')
        {
            if( row >= rectangle.start_row && row < rectangle.end_row 
            && (col - 1) > rectangle.left_col && (col - 1) < rectangle.right_col)
            {
                printf("%c", X);  
                rec_area--;

            }
            else if(rec_area > 0)
            {
                if((col - 1) > rectangle.left_col && (col - 1) < rectangle.right_col)
                {
                    printf("%c", X);  
                    rec_area--;
                }
                else
                printf("."); 
            }
            else
                printf("."); 
        }            
				
	}  

   

}

t_rectangle get_map2(register int *const fd)    
{
    int ret;
	char buf[1+1];
    int row;
    int col;
    int n;
    char s;
    t_rectangle rectangle;

    int s1;
    int s2;

    int rec_hight;
    int rec_width;
    
    //int j;

    LENGTH = 0;
    
    s1 = 0;
    s2 = 0;

    row = 1;
    col = 0;      
    n = 1;

    rec_width = COL_COUNT;
    rec_hight = 1;

    rectangle.start_row = 1;
    rectangle.end_row = 0;
    rectangle.left_col = 0;
    rectangle.right_col = 0;

    printf("\n****************SERCH RECTANGLE 2******************\n");
    while ((ret = read(*fd, buf, 1)))  
	{
        
        s = buf[0];
        buf[ret] = '\0';
        if(s == '\n') 
        {
            col = 0;
            row++;
           // printf("\n");
        }
        col++;
        if(row == 1)
        {
            continue;            
        }
        if(buf[0] == OB) 
        {
            
            if(rectangle.left_col != 0 && (col - 1) > rectangle.left_col && 
                (rectangle.right_col != 0) && (rectangle.right_col > (col - 1)))
            {
                rectangle.end_row = (col - 1);
                break;
            }
            if(rectangle.left_col == 0 || (col - 1) < rectangle.left_col)
                rectangle.left_col = (col - 1);
            else if(rectangle.right_col == 0)
                rectangle.right_col = (col - 1);            
        }                   
				
	}  
    rectangle.rec_area = (rectangle.end_row - rectangle.start_row) * (rectangle.right_col - rectangle.left_col); 
    
    return (rectangle);
}

