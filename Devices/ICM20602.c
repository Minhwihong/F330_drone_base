/**

 * ICM20602.c
 * @author ChrisP @ M-HIVE

 * This library source code has been created for STM32F4. Only supports SPI.
 *
 * Development environment specifics:
 * STM32CubeIDE 1.0.0
 * STM32CubeF4 FW V1.24.1
 * STM32F4 LL Driver(SPI) and HAL Driver(RCC for HAL_Delay() function)
 *
 * Created by ChrisP(Wonyeob Park) @ M-HIVE Embedded Academy, July, 2019
 * Rev. 1.0
 *
 * https://github.com/ChrisWonyeobPark/
 * https://www.udemy.com/course/stm32-drone-programming/?referralCode=E24CB7B1CD9993855D45
 * https://www.inflearn.com/course/stm32cubelde-stm32f4%EB%93%9C%EB%A1%A0-%EA%B0%9C%EB%B0%9C
*/

/**
 * @brief ICM20602 structure definition.
 */

#include "ICM20602.h"

/*
STM32F429 Disc 확인
spi1 OK  
	PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    PB4     ------> SPI1_MISO

spi2
    PC2     ------> SPI2_MISO
    PC3     ------> SPI2_MOSI
    PB10     ------> SPI2_SCK

spi3 X

spi4 OK
    PE2     ------> SPI4_SCK
    PE5     ------> SPI4_MISO
    PE6     ------> SPI4_MOSI
*/

extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi4;
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi3;

#define ICM20603_SPI		(hspi2)

ICM20602_t ICM20602;
int32_t gyro_x_offset, gyro_y_offset, gyro_z_offset; // To remove offset



#if 0
typedef enum 
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;
#endif



//////////////////////////////////////////////////////////////

uint8_t ICM20602_Readbyte(ISpi* pxSpi, uint8_t reg_addr)
{
	uint8_t val;
	uint8_t rtn = 0;

	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_RESET);
	ISpiChipSelect(pxSpi, 0);

	rtn = ISpiWriteByte(pxSpi, reg_addr | 0x80);	//Register. MSB 1 is read instruction.
	//val = SPI1_SendByte(0x00); //Send DUMMY to read data
	
	if(rtn != 0){
		return 0;
	}

	//HAL_SPI_Receive(&ICM20603_SPI, &val, 1, HAL_MAX_DELAY);
	ISpiReadByte(pxSpi, &val);
	
	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_SET);
	ISpiChipSelect(pxSpi, 1);
	
	return val;
}

void ICM20602_Readbytes(ISpi* pxSpi, unsigned char reg_addr, unsigned char len, unsigned char* data)
{
	unsigned int i = 0;

	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_RESET);
	ISpiChipSelect(pxSpi, 0);
	
	//SPI_SendByte(reg_addr | 0x80); //Register. MSB 1 is read instruction.
	ISpiWriteByte(pxSpi, reg_addr | 0x80);
	
	while(i < len)
	{
		//data[i++] = SPI1_SendByte(0x00); //Send DUMMY to read data
		//HAL_SPI_Receive(&ICM20603_SPI, &data[i], 1, 20);
		ISpiReadByte(pxSpi, &data[i]);
		i++;
	}

	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_SET);
	ISpiChipSelect(pxSpi, 1);
}

void ICM20602_Writebyte(ISpi* pxSpi, uint8_t reg_addr, uint8_t val)
{
	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_RESET);
	ISpiChipSelect(pxSpi, 0);

	// SPI_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
	// SPI_SendByte(val); //Send Data to write

	ISpiWriteByte(pxSpi, reg_addr & 0x7F);	//Register. MSB 0 is write instruction.
	ISpiWriteByte(pxSpi, val);				//Send Data to write

	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_SET);
	ISpiChipSelect(pxSpi, 1);
}

void ICM20602_Writebytes(ISpi* pxSpi, unsigned char reg_addr, unsigned char len, unsigned char* data)
{
	unsigned int i = 0;

	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_RESET);
	ISpiChipSelect(pxSpi, 0);
	
	//SPI_SendByte(reg_addr & 0x7F); //Register. MSB 0 is write instruction.
	ISpiWriteByte(pxSpi, reg_addr & 0x7F);	//Register. MSB 0 is write instruction.
	
	while(i < len)
	{
		ISpiWriteByte(pxSpi, data[i++]); //Send Data to write
	}
	
	//HAL_GPIO_WritePin(SPI_CS_ICM20602_GPIO_Port, SPI_CS_ICM20602_Pin, GPIO_PIN_SET);
	ISpiChipSelect(pxSpi, 1);
}


int ICM20602_Initialization(ISpi* pxSpi)
{

	uint8_t who_am_i = 0;
	// int16_t accel_raw_data[3] = {0};  // To remove offset
	// int16_t gyro_raw_data[3] = {0};   // To remove offset
	
	//ICM20602_GPIO_SPI_Initialization();
	
	printf("Checking ICM20602...");
	
	// check WHO_AM_I (0x75)
	who_am_i = ICM20602_Readbyte(pxSpi, WHO_AM_I); 

	// who am i = 0x12
	if(who_am_i == 0x12)
	{
		printf("\nICM20602 who_am_i = 0x%02x...OK\n\n", who_am_i);
	}
	// recheck
	else if(who_am_i != 0x12)
	{
		who_am_i = ICM20602_Readbyte(pxSpi, WHO_AM_I); // check again WHO_AM_I (0x75)

		if (who_am_i != 0x12){
			printf( "ICM20602 Not OK: 0x%02x Should be 0x%02x\n", who_am_i, 0x12);
			return 1; //ERROR
		}
	}
	
	// Reset ICM20602
	// PWR_MGMT_1 0x6B
	ICM20602_Writebyte(pxSpi, PWR_MGMT_1, 0x80); //Reset ICM20602
	HAL_Delay(50);

	// PWR_MGMT_1 0x6B
	ICM20602_Writebyte(pxSpi, PWR_MGMT_1, 0x01); // Enable Temperature sensor(bit4-0), Use PLL(bit2:0-01)
									// 온도센서 끄면 자이로 값 이상하게 출력됨
	HAL_Delay(50);

	// PWR_MGMT_2 0x6C
	ICM20602_Writebyte(pxSpi, PWR_MGMT_2, 0x38); // Disable Acc(bit5:3-111), Enable Gyro(bit2:0-000)
	//ICM20602_Writebyte( PWR_MGMT_2, 0x00 ); // Enable Acc(bit5:3-000), Enable Gyro(bit2:0-000)
	HAL_Delay(50);
	
	// set sample rate to 1000Hz and apply a software filter
	ICM20602_Writebyte(pxSpi, SMPLRT_DIV, 0x00);
	HAL_Delay(50);
	
	// Gyro DLPF Config
	//ICM20602_Writebyte(CONFIG, 0x00); // Gyro LPF fc 250Hz(bit2:0-000)
	ICM20602_Writebyte(pxSpi, CONFIG, 0x05); // Gyro LPF fc 20Hz(bit2:0-100) at 1kHz sample rate
	HAL_Delay(50);

	// GYRO_CONFIG 0x1B
	ICM20602_Writebyte(pxSpi, GYRO_CONFIG, 0x18); // Gyro sensitivity 2000 dps(bit4:3-11), FCHOICE (bit1:0-00)
	HAL_Delay(50);

	// ACCEL_CONFIG 0x1C
	ICM20602_Writebyte(pxSpi, ACCEL_CONFIG, 0x18); // Acc sensitivity 16g
	HAL_Delay(50);
	
	// ACCEL_CONFIG2 0x1D
	ICM20602_Writebyte(pxSpi, ACCEL_CONFIG2, 0x03); // Acc FCHOICE 1kHz(bit3-0), DLPF fc 44.8Hz(bit2:0-011)
	HAL_Delay(50);
	
	// Enable Interrupts when data is ready
	ICM20602_Writebyte(pxSpi, INT_ENABLE, 0x01); // Enable DRDY Interrupt
	HAL_Delay(50);
	
	//printf("gyro bias: %d %d %d\n", gyro_x_offset, gyro_y_offset, gyro_z_offset);
	
	// Remove Gyro X offset
//	ICM20602_Writebyte( XG_OFFS_USRH, offset_x>>8 );	// gyro x offset high byte
//	ICM20602_Writebyte( XG_OFFS_USRL, offset_x );	// gyro x offset low byte
//	
//	// Remove Gyro Y offset
//	ICM20602_Writebyte( YG_OFFS_USRH, offset_y>>8 );	// gyro y offset high byte
//	ICM20602_Writebyte( YG_OFFS_USRL, offset_y );	// gyro y offset low byte
//	
//	// Remove Gyro Z offset
//	ICM20602_Writebyte( ZG_OFFS_USRH, offset_z>>8 );	// gyro z offset high byte
//	ICM20602_Writebyte( ZG_OFFS_USRL, offset_z );	// gyro z offset low byte

	return 0; //OK
}

void ICM20602_Get6AxisRawData(ISpi* pxSpi, short* accel, short* gyro)
{
	unsigned char data[14];
	ICM20602_Readbytes(pxSpi, ACCEL_XOUT_H, 14, data);
	
	accel[0] = (data[0] << 8) | data[1];
	accel[1] = (data[2] << 8) | data[3];
	accel[2] = (data[4] << 8) | data[5];

	gyro[0] = ((data[8] << 8) | data[9]);
	gyro[1] = ((data[10] << 8) | data[11]);
	gyro[2] = ((data[12] << 8) | data[13]);
}

void ICM20602_Get3AxisGyroRawData(ISpi* pxSpi, short* gyro)
{
	unsigned char data[6];
	ICM20602_Readbytes(pxSpi, GYRO_XOUT_H, 6, data);
	
	gyro[0] = ((data[0] << 8) | data[1]);
	gyro[1] = ((data[2] << 8) | data[3]);
	gyro[2] = ((data[4] << 8) | data[5]);
}

void ICM20602_Get3AxisAccRawData(ISpi* pxSpi, short* accel)
{
	unsigned char data[6];
	ICM20602_Readbytes(pxSpi, ACCEL_XOUT_H, 6, data);
	
	accel[0] = ((data[0] << 8) | data[1]);
	accel[1] = ((data[2] << 8) | data[3]);
	accel[2] = ((data[4] << 8) | data[5]);
}

int ICM20602_DataReady(void)
{
	return HAL_GPIO_ReadPin(GPE_ICM20602_INT_GPIO_Port, GPE_ICM20602_INT_Pin);
}
