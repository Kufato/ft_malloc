#include "inc/malloc.h"

int main(void)
{
    size_t  size = sizeof(char) * 5; 
    char    *tab = malloc(size);
    if (tab == NULL)
    {
        perror("malloc");
        return (1);
    }

    for (int i = 0; i < 5; i++)
        tab[i] = ft_itoa(i)[0];
    
    for (int i = 0; i < 5; i++)
        ft_putchar_fd(tab[i], 1);
    
    free(tab);
    return (0);
}