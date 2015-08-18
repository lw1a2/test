#include <stdio.h>
#include <string.h>

int main()
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

    return 0;
}
