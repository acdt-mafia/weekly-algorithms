// 크로아티아 알파벳
#include <stdio.h>

int main()
{
    char str[101];

    scanf("%s", str);

    int word = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '=' || str[i] == '-')
        {
            word = word;
            if (str[i - 1] == 'z' && str[i - 2] == 'd')
                word = word - 1;
        }

        else if (str[i] == 'j')
        {
            if (str[i - 1] == 'l' || str[i - 1] == 'n')
                word = word;
            else
                word++;
        }
        else
            word++;
    };
    printf("%d", word);
}