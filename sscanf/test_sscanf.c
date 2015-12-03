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

int main()
{
    f2();

    return 0;
}
