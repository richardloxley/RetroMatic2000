/* based on GBS_Control
 *  https://github.com/mybook4/DigisparkSketches/tree/master/GBS_Control
 */

#include "i2c.h"
#include "video_R_start.h"
#include "video_R_288p.h"


#define GBS_I2C_ADDRESS 0x17 // 0x2E
I2CBitBanger i2cObj(GBS_I2C_ADDRESS);


bool writeOneByte(uint8_t slaveRegister, uint8_t value)
{
	return writeBytes(slaveRegister, &value, 1); 
}


bool writeBytes(uint8_t slaveAddress, uint8_t slaveRegister, uint8_t* values, uint8_t numValues)
{
	/*
	Write to Consecutive Control Registers:
	-Start Signal 
	-Slave Address Byte (R/W Bit = Low) 
	-Base Address Byte 
	-Data Byte to Base Address 
	-Data Byte to (Base Address + 1) 
	-Data Byte to (Base Address + 2) 
	-Data Byte to (Base Address + 3) 
	.................. 
	-Stop Signal
	*/
	
	//i2cObj.setSlaveAddress(slaveAddress);
	
	i2cObj.addByteForTransmission(slaveRegister);
	
	i2cObj.addBytesForTransmission(values, numValues);
	
	if(!i2cObj.transmitData())
	{    
		return false;
	}
	
	return true;
}


bool writeBytes(uint8_t slaveRegister, uint8_t* values, int numValues)
{
	return writeBytes(GBS_I2C_ADDRESS, slaveRegister, values, numValues);
}


bool writeStartArray()
{
	for (int z = 0; z < ((sizeof(startArray)/2) - 1520); z++)
	{
		if (writeOneByte(pgm_read_byte(startArray + (z*2)), pgm_read_byte(startArray + (z*2) + 1)))
		{
			if (z % 50 == 0)
			{
				//Serial.println("");
			}
		}
		else
		{
			//Serial.println("Failed to write start register");
		}
		
		delay(1);
	}
	
	//Serial.println("");
	
	return true;
}


bool writeProgramArray(const uint8_t* programArray)
{ 
	for(int y = 0; y < 6; y++)
	{ 
		writeOneByte(0xF0, (uint8_t)y);
		delay(1);
		
		for (int z = 0; z < 15; z++)
		{
			uint8_t bank[16];
			for(int w = 0; w < 16; w++)
			{
				bank[w] = pgm_read_byte(programArray + (y*256 + z*16 + w));
			}

			writeBytes(z*16, bank, 16);
			
			delay(1);
		}
	}
	
	return true;
}


void setUpVideoBoard()
{
	writeStartArray();
    writeProgramArray(programArray288p50);
}

