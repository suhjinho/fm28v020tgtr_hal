/* 		COMPANY:NSTEK  	SUHJINHO 01076768380		 		*/

/*			FM28V020TGTR									*/

/* Chip Select : NE1,  Address data : 15bits(A0 ~ A14) ,  Data : 8bits            */


/* NOR/PSRAM control															  */
/* Bank : Bank 1 NOR/PSRAM 1,  Write operation : Enabled, Extended mode : Enabled */


/* NOR/PSRAM timing															 	  */
/* Address setup time in HCLK clock cycles   : 15  							      */
/* Data setup time in HCLK clock cycles      : 255								  */
/* Bus turn around time in HCLK clock cycles : 15							      */
/* Access mode								 : A								  */


/* NOR/PSRAM timing	for write accesses											  */
/* Extended address setup time			     : 15  							      */
/* Extended data setup time				     : 255								  */
/* Extended bus turn around time			 : 3							      */
/* Extended access mode		 			     : A								  */



#ifndef __fm28v020_tgtr_H__
#define __fm28v020_tgtr_H__

SRAM_HandleTypeDef hsram1;


void FM28V020TGTR_write(SRAM_HandleTypeDef select_sram, uint32_t sram_Address, uint8_t *write_data, uint32_t sram_BufferSize); /* sram_Address = 0~3FFFFFFF 입력  	*/
/* ADDRESS DATA >= 0X60000000 && ADDRESS DATA < 0X64000000					  */
/* 주소 DATA 0x60000000 번지 이상 0x64000000 번지 미만								  */

/* Data write above 0x64000000 results in HardFault_Handler function		  */
/* 0x64000000 번지 이상으로 data write 할 시 HardFault_Handler 함수 발생 			  */


/* read_data < 256	256이상 data write 시 	overflow_number -255 적용			  */

void FM28V020TGTR_read(SRAM_HandleTypeDef select_sram, uint32_t sram_Address, uint8_t *read_data, uint32_t sram_BufferSize);
/* ADDRESS DATA >= 0X60000000 && ADDRESS DATA < 0X64000000					  */
/* 주소 DATA 0x60000000 번지 이상 0x64000000 번지 미만					 			  */

/* Data read above 0x64000000 results in HardFault_Handler function		  	  */
/* 0x64000000 번지 이상으로 data read 할 시 HardFault_Handler 함수 발생 				  */





#define SRAM_INIT_ADDRESS  0x60000000  	   	/* data write or data read initial address   */
											/* data write or data read 시작 주소  			 */

#define SRAM_MAX_ADDRESS   0x63FFFFFF    	/* data write or data read last address	     */
											/* data write or data read 마지막 주소  		 */




void FM28V020TGTR_write(SRAM_HandleTypeDef select_sram, uint32_t sram_Address, uint8_t *write_data, uint32_t sram_BufferSize)
{
	/* sram_Address = 0~3FFFFFFF 입력  	*/
	/* sram_Address = 0~3FFFFFFF Enter  */
  if ((sram_Address + sram_BufferSize + SRAM_INIT_ADDRESS) < SRAM_MAX_ADDRESS )
  {
	  HAL_SRAM_Write_8b(&select_sram,(sram_Address+0x60000000),(uint8_t *)write_data, sram_BufferSize);
  }

}



void FM28V020TGTR_read(SRAM_HandleTypeDef select_sram, uint32_t sram_Address, uint8_t *read_data, uint32_t sram_BufferSize) 		/* sram_Address = 0~3FFFFFFF 입력  	*/
{																																	/* sram_Address = 0~3FFFFFFF input  */

	if ((sram_Address + sram_BufferSize + SRAM_INIT_ADDRESS) < SRAM_MAX_ADDRESS)
  {
	  HAL_SRAM_Read_8b(&select_sram, (sram_Address+0x60000000), (uint8_t*)read_data, sram_BufferSize);
  }

}


static void MX_FMC_Init(void) {

	FMC_NORSRAM_TimingTypeDef Timing = { 0 };
	FMC_NORSRAM_TimingTypeDef ExtTiming = { 0 };


	hsram1.Instance = FMC_NORSRAM_DEVICE;
	hsram1.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
	/* hsram1.Init */
	hsram1.Init.NSBank = FMC_NORSRAM_BANK1;
	hsram1.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
	hsram1.Init.MemoryType = FMC_MEMORY_TYPE_PSRAM;
	hsram1.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_8;
	hsram1.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
	hsram1.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
	hsram1.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
	hsram1.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
	hsram1.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
	hsram1.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
	hsram1.Init.ExtendedMode = FMC_EXTENDED_MODE_ENABLE;
	hsram1.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
	hsram1.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
	hsram1.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
	hsram1.Init.PageSize = FMC_PAGE_SIZE_NONE;
	/* Timing */
	Timing.AddressSetupTime = 15;
	Timing.AddressHoldTime = 15;
	Timing.DataSetupTime = 255;
	Timing.BusTurnAroundDuration = 15;
	Timing.CLKDivision = 16;
	Timing.DataLatency = 17;
	Timing.AccessMode = FMC_ACCESS_MODE_A;
	/* ExtTiming */
	ExtTiming.AddressSetupTime = 15;
	ExtTiming.AddressHoldTime = 15;
	ExtTiming.DataSetupTime = 255;
	ExtTiming.BusTurnAroundDuration = 3;
	ExtTiming.CLKDivision = 16;
	ExtTiming.DataLatency = 17;
	ExtTiming.AccessMode = FMC_ACCESS_MODE_A;

	if (HAL_SRAM_Init(&hsram1, &Timing, &ExtTiming) != HAL_OK) {
		Error_Handler();
	}
}
#endif
