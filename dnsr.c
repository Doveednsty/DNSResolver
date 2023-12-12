#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <доменное_имя>\n", argv[0]);
        return 1;
    }

    const char *domain_name = argv[1];
    struct hostent *host_info;

    // Получаем информацию о хосте по его доменному имени
    host_info = gethostbyname(domain_name);

    if (host_info == NULL) {
        herror("Ошибка при разрешении доменного имени");
        return 2;
    }

    printf("Доменное имя: %s\n", host_info->h_name);

    // Выводим все IP-адреса, связанные с данным доменным именем
    printf("IP-адреса:\n");
    for (int i = 0; host_info->h_addr_list[i] != NULL; i++) {
        struct in_addr *address = (struct in_addr*) host_info->h_addr_list[i];
        printf("%s\n", inet_ntoa(*address));
    }

    return 0;
}
