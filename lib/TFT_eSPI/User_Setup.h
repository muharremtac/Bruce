#define ST7789_DRIVER     // ST7789 seçili

// ... Diğer tanımlamalar ...

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// ... Pin tanımları (Kartınıza göre değişebilir) ...
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   5  // Chip select control pin
#define TFT_DC   16  // Data Command control pin
#define TFT_RST  23  // Reset pin (could connect to RST pin)
#define TFT_BL   32  // LED back-light

// ... SPI Frekans Ayarları ...
#define SPI_FREQUENCY      40000000 // 40 MHz, ST7789 için maksimum değer
#define SPI_READ_FREQUENCY 20000000
#define SPI_TOUCH_FREQUENCY 2500000