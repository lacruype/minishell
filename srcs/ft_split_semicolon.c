#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int        nombre_mots(char const *str, char c)
{
    int i;
    int mots;

    i = 0;
    mots = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            i++;
            while (str[i] != '"' && str[i])
                i++;
        }
        if (str[i] == '\'')
        {
            i++;
            while (str[i] != '\'' && str[i])
                i++;
        }
        while (str[i] == c)
            i++;
        if (str[i] != c && str[i] != '\0' && str[i] != '"' && str[i] != '\'')
            mots++;
        while (str[i] != c && str[i] != '\0' && str[i] != '"' && str[i] != '\'')
        {
            i++;
        }
    }
    printf("NB_MOTS = [%d]\n", mots);
    return (mots);
}

static char    **taille_mots(char const *str, char c, char **tab)
{
    int i;
    int mots;
    int taille;

    i = 0;
    taille = 0;
    mots = 0;
    while (1)
    {
        if (str[i] == '"')
        {
            taille++;
            i++;
            while (str[i] != '"' && str[i])
            {
                taille++;
                i++;
            }
        }
        else if (str[i] == '\'')
        {
            taille++;
            i++;
            while (str[i] != '\'' && str[i])
            {
                taille++;
                i++;
            }
        }
        else if (str[i] == c || str[i] == '\0')
        {
            if (!(tab[mots] = malloc(sizeof(char) * taille + 1)))
              return (0);
            mots++;
            taille = 0;
            if(str[i] == '\0')
              return (tab);
            i++;
        }
        else
        {
          i++;
          taille++;
        }
    }
    return (tab);
}

static char    **place_mots(char const *str, char c, char **tab)
{
    int i;
    int mots;
    int taille;

    i = 0;
    taille = 0;
    mots = 0;
    while (1)
    {
        if (str[i] == '"')
        {
          tab[mots][taille] = str[i];
            taille++;
            i++;
            while (str[i] != '"' && str[i])
            {
              tab[mots][taille] = str[i];
                taille++;
                i++;
            }
        }
        else if (str[i] == '\'')
        {
          tab[mots][taille] = str[i];
            taille++;
            i++;
            while (str[i] != '\'' && str[i])
            {
              tab[mots][taille] = str[i];
                taille++;
                i++;
            }
        }
        else if (str[i] == c || str[i] == '\0')
        {
            tab[mots][taille] = '\0';
            mots++;
            taille = 0;
            if(str[i] == '\0')
              return (tab);
            i++;
        }
        else
        {
          tab[mots][taille] = str[i];
          i++;
          taille++;
        }
    }
    return (tab);
}

char    **ft_split_semicolon(char const *s, char c)
{
    int        i;
    int        nb_mots;
    char    **tab;

    i = 0;
    nb_mots = nombre_mots(s, c);
    if (!(tab = malloc(sizeof(char*) * (nb_mots + 1))))
        return (0);
    tab[nb_mots] = NULL;
    taille_mots(s, c, tab);
    place_mots(s, c, tab);
    if (tab[nb_mots] && tab[nb_mots][0] == '\0')
        free(tab[nb_mots]);
    tab[nb_mots] = NULL;
    return (tab);
}

int main(int ac, char **av)
{
    char **tab;
    char str[20] = "Salut\";\"Yes";
    int i;

    i = 0;

    tab = ft_split_semicolon(av[1], ';');
    while (tab[i])
    {
        printf("tab[%d] = [%s]\n", i, tab[i]);
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}

