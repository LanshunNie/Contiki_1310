#include "ti-lib.h"
#include "flashdata.h"
#include "cpu/cc26xx-cc13xx/lib/cc13xxware/driverlib/flash.h"

int write_to_flash(){

	int32_t result;
	uint8_t packet[8]={5,5,5,5};
	/*Disable the cache*/
	VIMSModeSet(VIMS_BASE, VIMS_MODE_DISABLED);
  	while(VIMSModeGet(VIMS_BASE)!=VIMS_MODE_DISABLED);

  	/*make sure the sector isn't write protected*/
  	result = FlashProtectionGet(SECTOR_TO_ERASE_START_ADDR);
  	if(result == FLASH_WRITE_PROTECT){
  		return 1;
  	}

  	/*Disable all interrupts when accessing the flash*/
  	CPUcpsid();

  	/*Erase a flash Page*/
  	// result = FlashSectorErase(SECTOR_TO_ERASE_START_ADDR);

  	// if(result != FAPI_STATUS_SUCCESS){
   //  		return 1;
   //  }
    /* Program 128 bytes in chunks of 8 bytes */
    
  		/*Programs unprotected main bank flash sectors*/
    	result = FlashProgram(&packet[0],SECTOR_TO_ERASE_START_ADDR,8);

    	if(result != FAPI_STATUS_SUCCESS){

    		return 1;
    	}

    


    CPUcpsie();

    /*Re-enable the cache*/
    VIMSModeSet(VIMS_BASE, VIMS_MODE_ENABLED);
   	
	return 0;
}

void read_flash( uint32_t wAddr,uint8_t *bBuf,uint8_t bLen){

	uint8_t *Flash_Ptr =(uint8_t *)wAddr;
	while(bLen--){
		*(bBuf++) = *(Flash_Ptr);
	}

}

