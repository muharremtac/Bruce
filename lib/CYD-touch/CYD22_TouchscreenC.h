/* Touchscreen library for 2432W328 Capacitive Touch Controller Chip
 * Supported boards
 *  - 2432W328C
 */

#include <Wire.h>

// These definitions come from https://github.com/rzeldent/platformio-espressif32-sunton board definitions
#if defined (TOUCH_CST816S_I2C)
    #define CYD22_TouchC_SDA 21
    #define CYD22_TouchC_SCL 22
    #define CYD22_TouchC_INT GPIO_NUM_NC
    #define CYD22_TouchC_RST GPIO_NUM_NC
    #define CYD22_I2C_ADDR 0x15
//  #elif defined(TOUCH_GT911_I2C) // Not implemented
//      #define CYD22_TouchC_SDA GT911_I2C_CONFIG_SDA_IO_NUM
//      #define CYD22_TouchC_SCL GT911_I2C_CONFIG_SCL_IO_NUM
//      #define CYD22_TouchC_INT GT911_TOUCH_CONFIG_RST_GPIO_NUM
//      #define CYD22_TouchC_RST GT911_TOUCH_CONFIG_INT_GPIO_NUM
//      #define CYD22_I2C_ADDR 0x5D
#else
    #define CYD22_I2C_ADDR 0x15
    #define CYD22_TouchC_SDA 33
    #define CYD22_TouchC_SCL 32
    #define CYD22_TouchC_INT 21
    #define CYD22_TouchC_RST 25
#endif
class CYD22_TS_Point {
public:
  CYD22_TS_Point(void) : x(0), y(0), z(0) {}
  CYD22_TS_Point(int16_t x, int16_t y, int16_t z) : x(x), y(y), z(z) {}
  int16_t x, y, z; // z is not used, but kept for compatibility of TouchscreenR
};

class CYD22_TouchC {
public:
    constexpr CYD22_TouchC(int16_t w, int16_t h)
        : sizeX_px(w), sizeY_px(h){ }
    bool begin(void);
    bool touched();
    CYD22_TS_Point getPointScaled();
    void setRotation(uint8_t n) { rotation = n % 4; }

private:
    const int16_t sizeX_px;
    const int16_t sizeY_px;
    uint8_t rotation=1;
    uint8_t i2c_read(uint8_t addr);
    uint8_t i2c_read_continuous(uint8_t addr, uint8_t *data, uint32_t length);
    void i2c_write(uint8_t addr, uint8_t data);
    CYD22_TS_Point convertRawXY(int16_t x, int16_t y);
};