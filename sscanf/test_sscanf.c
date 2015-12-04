#include <stdio.h>
#include <string.h>

void f()
{
    char *line = "port1=12345";
    char port_name[16];
    char pci_id[16];
    bzero(port_name, sizeof(port_name));
    bzero(pci_id, sizeof(pci_id));
    // 这样写是避免贪婪
    sscanf(line, "%[^=]=%s", port_name, pci_id);

    printf("port_name: %s\n", port_name);
    printf("pci_id: %s\n", pci_id);
}

void f2()
{
    char *s = "/captcha.html?captcha=mapkh";
    char captcha_name[2];
    bzero(captcha_name, sizeof(captcha_name));
    char captcha_value[6];
    bzero(captcha_value, sizeof(captcha_value));
    char prefix[256];
    bzero(prefix, sizeof(prefix));
    sscanf(s, "%[^?]?%[^=]=%s", prefix, captcha_name, captcha_value);

    printf("prefix: %s\n", prefix);
    printf("captcha_name: %s\n", captcha_name);
    printf("captcha_value: %s\n", captcha_value);
}

char *trim(char *str)
{
    char *p = str;
    char *p1;
    if (p)
    {
        p1 = p + strlen(str) - 1;
        while (*p && isspace(*p)) p++;
        while (p1 > p && isspace(*p1)) *p1-- = '\0';
    }
    return p;
}


void f3()
{
    char s[] = "ABC=1; DEF=2; H=3";
    char name[256];
    bzero(name, sizeof(name));
    char value[256];
    bzero(value, sizeof(value));

    char *p = strtok(s, ";");
    if (p) {
        p = trim(p);
        printf("%s\n", p);

        sscanf(p, "%[^=]=%s", name, value);
        printf("name: %s\n", name);
        printf("value: %s\n", value);
        printf("\n");
    }
    while(p = strtok(NULL, ";")) {
        p = trim(p);
        printf("%s\n", p);

        sscanf(p, "%[^=]=%s", name, value);
        printf("name: %s\n", name);
        printf("value: %s\n", value);
        printf("\n");
    }
}

int main()
{
    f3();

    return 0;
}
