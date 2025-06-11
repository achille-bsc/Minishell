#include "headers/minishell.h"
#include <stdio.h>

int main(void)
{
    t_mnours data;

    // Initialisation basique
    memset(&data, 0, sizeof(t_mnours));
    data.line = "echo \"Only Simple''\"\"''\"";

    printf("Test de parsing: %s\n", data.line);

    set_token(&data);

    // Affichage des résultats
    write_args(data.ex);

    return 0;
}
