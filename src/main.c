#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{
    int err, dev_id, sock, len, max_rsp, num_rsp;
    int flags;
    char addr[19] = { 0 };
    char name[248] = { 0 };
    inquiry_info *ii = NULL;

    // Get the first available Bluetooth adapter
    dev_id = hci_get_route(NULL);
    if (dev_id < 0) {
        perror("No Bluetooth Adapter Available");
        exit(1);
    }

    // Open a socket to the adapter
    sock = hci_open_dev(dev_id);
    if (sock < 0) {
        perror("Failed to open socket to adapter");
        exit(1);
    }

    len = 8;        // Inquiry lasts for 8 * 1.28 = 10.24 seconds
    max_rsp = 255;  // Maximum number of responses
    flags = IREQ_CACHE_FLUSH;  // Flush the cache of previously discovered devices

    // Allocate memory for inquiry results
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));

    // Perform Bluetooth device inquiry
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    if (num_rsp < 0) {
        perror("HCI inquiry failed");
        free(ii);
        exit(1);
    }

    printf("Number of Bluetooth devices found: %d\n", num_rsp);

    // Print the addresses and names of found devices
    for (int i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), name, 0) < 0)
            strcpy(name, "[unknown]");

        printf("%s  %s\n", addr, name);
    }

    // Free resources
    free(ii);
    close(sock);

    return 0;
}
