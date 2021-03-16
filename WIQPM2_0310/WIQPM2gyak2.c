#include <stdio.h>
#include <stdlib.h>

int main()
{
    char parancs[250];
    printf("Parancs: ");
    scanf("%s", parancs);
    system(parancs);

    return 0;
}
