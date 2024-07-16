#include "inc/malloc.h"

int main(void)
{
    size_t	size = sizeof(int) * 5; 
    int		*tab = malloc(size);
    if (tab == NULL)
    {
        perror("malloc");
        return (1);
    }

    for (int i = 0; i < 5; i++)
        tab[i] = i;
    
    for (int i = 0; i < 5; i++)
        printf("tab[%d] = %d\n", i, tab[i]);
    
    free(tab);
    return (0);
}