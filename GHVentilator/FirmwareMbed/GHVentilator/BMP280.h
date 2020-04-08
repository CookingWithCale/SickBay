/**
 *  BME280 Combined humidity and pressure sensor library
 *
 *  @author  Toyomasa Watarai
 *  @version 1.0
 *  @date    06-April-2015
 *
 *  Library for "BME280 temperature, humidity and pressure sensor module" from Switch Science
 *    https://www.switch-science.com/catalog/2236/
 *
 *  For more information about the BME280:
 *    http://ae-bst.resource.bosch.com/media/products/dokumente/bme280/BST-BME280_DS001-10.pdf
 */
 
#ifndef MbedBME280Decl
#define MbedBME280Decl

#include <mbedBug.h>

//#define _DEBUG
// default address with SDO High 0x77
// address with SDO LOW 0x76
#define SlaveAddressDefault (0x77)

 
/** A BME280 environmental sensor
A library to read environmental temperature and pressure using Bosch BME280. */
 
class BMP280 {
  public:
  
    enum {
      SlaveAddress = SlaveAddressDefault  //< The default I2C slave address.
    };

    /* Creates a BME280 instance connected to specified I2C pins and address.
    @param SDA I2C-bus SDA pin
    @param SCL I2C-bus SCL pin
    @param SlaveAddress (option) I2C-bus address (default: 0x77) */
    BMP280(PinName SDA, PinName SCK, char SlaveAddress = SlaveAddressDefault);

    /* Creates a BME280 instance connected to the I2C pins and address.
     *
     * @param i2c_obj I2C object (instance)
     * @param SlaveAddress (option) I2C-bus address (default: 0x77)
     */
    BMP280(I2C &i2c_obj, char SlaveAddress = SlaveAddressDefault);

    ~BMP280();

    /* Initializa BME280 sensor
    Configure sensor setting and read parameters for calibration */
    void Initialize(void);

    /* Read the current temperature value (degree Celsius) from BME280 sensor */
    float Temperature(void);

    /* Read the current pressure value (hectopascal)from BME280 sensor */
    float Pressure(void);

    /* Read the current humidity value (humidity %) from BME280 sensor */
    //float HumidityGet(void);

private:

    I2C         *i2c_p;
    I2C         &i2c;
    char        address;
    uint16_t    dig_T1;
    int16_t     dig_T2, dig_T3;
    uint16_t    dig_P1;
    int16_t     dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    uint16_t    dig_H1, dig_H3;
    int16_t     dig_H2, dig_H4, dig_H5, dig_H6;
    int32_t     t_fine;

};

#undef SlaveAddressDefault
#endif //< MbedBME280Decl
