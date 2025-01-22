/* Touchscreen library for 2432W328 Capacitive Touch Controller Chip
 * Supported boards
 *  - 2432W328C
 */

#include "CYD22_TouchscreenC.h"

static CYD22_TouchC *isrPinptr;

bool CYD22_TouchC::begin(void)
{


    auto _sda = CYD22_TouchC_SDA;
    auto _scl = CYD22_TouchC_SCL;
    auto _rst = CYD22_TouchC_RST;
    auto _int = CYD22_TouchC_INT;
    // Initialize I2C
    if (_sda != -1 && _scl != -1)
    {
        Wire.begin(_sda, _scl);
    }
    else
    {
        Wire.begin();
    }

    // Int Pin Configuration
    if (_int != -1)
    {
        pinMode(_int, OUTPUT);
        digitalWrite(_int, HIGH);
        delay(1);
        digitalWrite(_int, LOW); 
        delay(1);
    }

    // Reset Pin Configuration
    if (_rst != -1)
    {
        pinMode(_rst, OUTPUT);
        digitalWrite(_rst, LOW);
        delay(10);
        digitalWrite(_rst, HIGH);
        delay(300);
    }

    // Initialize Touch
    i2c_write(0xFE, 0XFF);
    isrPinptr = this;
    return true;
}

bool CYD22_TouchC::touched()
{
    bool FingerIndex = false;
    FingerIndex = (bool)i2c_read(0x02);

    return FingerIndex;
}

CYD22_TS_Point CYD22_TouchC::getPointScaled()
{
    uint8_t data[4];
    uint16_t x, y;
    i2c_read_continuous(0x03,data,4);
    x = ((data[0] & 0x0f) << 8) | data[1];
    y = ((data[2] & 0x0f) << 8) | data[3];
    return convertRawXY(x, y);
}

uint8_t CYD22_TouchC::i2c_read(uint8_t addr)
{
    uint8_t rdData;
    uint8_t rdDataCount;
    do
    {
        Wire.beginTransmission(CYD22_I2C_ADDR);
        Wire.write(addr);
        Wire.endTransmission(false); // Restart
        rdDataCount = Wire.requestFrom(CYD22_I2C_ADDR, 1);
    } while (rdDataCount == 0);
    while (Wire.available())
    {
        rdData = Wire.read();
    }
    return rdData;
}

uint8_t CYD22_TouchC::i2c_read_continuous(uint8_t addr, uint8_t *data, uint32_t length)
{
  Wire.beginTransmission(CYD22_I2C_ADDR);
  Wire.write(addr);
  if ( Wire.endTransmission(true))return -1;
  Wire.requestFrom(CYD22_I2C_ADDR, length);
  for (int i = 0; i < length; i++) {
    *data++ = Wire.read();
  }
  return 0;
}

void CYD22_TouchC::i2c_write(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission(CYD22_I2C_ADDR);
    Wire.write(addr);
    Wire.write(data);
    Wire.endTransmission();
}

CYD22_TS_Point CYD22_TouchC::convertRawXY(int16_t x, int16_t y) {
    int16_t convertX = y;
    int16_t convertY = sizeX_px - 1 - x;
    return CYD22_TS_Point(convertX, convertY, 0);
}