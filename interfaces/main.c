#include <stdio.h>
#include <uv.h>

int main(void) {
  char buffer[512];
  uv_interface_address_t *info;
  int count = 0, i = 0;

  uv_interface_addresses(&info, &count);
  i = count;

  printf("Number of interfaces: %d\n", count);
  while(i--) {
    uv_interface_address_t interface = info[i];

    printf("Interface name: %s\n", interface.name);
    printf("Internal interface? %s\n", interface.is_internal ? "Yes" : "No");

    if(interface.address.address4.sin_family == AF_INET) {
      uv_ip4_name(&interface.address.address4, buffer, sizeof(buffer));
      printf("IPv4 address: %s\n", buffer);
    }
    else if(interface.address.address4.sin_family == AF_INET6) {
      uv_ip6_name(&interface.address.address6, buffer, sizeof(buffer));
      printf("IPv6 address: %s\n", buffer);
    }
    printf("\n\n");
  }

  uv_free_interface_addresses(info, count);

  return 0;
}
