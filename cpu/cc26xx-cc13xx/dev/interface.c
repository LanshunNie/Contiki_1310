#include "contiki.h"
#include "dev/interface.h"
#include "net/packetbuf.h"

#include <stdio.h>
#include <string.h>
static unsigned char *original_dataptr;

void packet_input_test(int len){
	original_dataptr = packetbuf_dataptr();
	printf("length: %d\n",len);
	printf("%s\n",original_dataptr);
}
