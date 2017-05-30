#ifndef FLASHDATA_H_
#define FLASHDATA_H_

/*Flash defines*/

#define SECTOR_SIZE      4096
#define SECTOR_TO_ERASE      14
#define SECTOR_TO_ERASE_START_ADDR   0x1f100
#define SECTOR_TO_ERASE_LENGTH 0xfa8  //waring: Don't overstep the boundary,this area contain net configuration information.
									//they are very important
/*The area in flash where the payload will be placed.SECTOR_SIZE * SECTOR_TO_ERASE*/
const char flashDataAddr[10]; //

int write_to_flash();
void read_flash( uint32_t wAddr,uint8_t *bBuf,uint8_t bLen);



#endif /* FLASHDATA_H_ */