#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char ** argv)
{
  int dev_id, sock;
  char addr[18] = "00:CD:FE:CE:BC:4D";
  bdaddr_t *ba = (bdaddr_t *)malloc(sizeof(bdaddr_t *));
  char * name = (char *)calloc(25,1);

  uint16_t test = 0;
  struct hci_dev_info di;
  
  if (0 > str2ba(addr,ba))
    {
      printf("str2ba() error\n");
      exit(1);
    }// end string 2 ba error


  dev_id = hci_get_route(NULL);
  sock = hci_open_dev( dev_id );
  if (dev_id < 0 || sock < 0) {
    perror("opening socket");
    exit(1);
  }

  if (0 > hci_devinfo(dev_id,&di))
    {
      printf("can't get device info\n");
      exit(1);
    }// end get device info

  
  if (hci_read_remote_name(sock, ba, 25,name, 0) < 0)
    {
      printf("unable to read name\n");
      exit(1);
    }
  printf("%s\n",name);

  if (0 > hci_create_connection(sock, ba, htobs(di.pkt_type & ACL_PTYPE_MASK),0,0x01,&test,25000))
    {
      perror("hci_create_connection error\n");
      exit(1);
    }//end if create connection

  if (0 > hci_disconnect(sock,test,0,0))
    {
      printf("hci_disconnect error\n");
      exit(1);
    }//end hci_disconnect
  
  close( sock );
  free(ba);
  free(name);
  return 0;
}// end main()
