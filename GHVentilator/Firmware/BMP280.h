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
#pragma once
#ifndef BME280MbedDecl
#define BME280MbedDecl
 
#include <mbedBug.h>
 
//#define _DEBUG
// default BusAddress with SDO High 0x77
// BusAddress with SDO LOW 0x76
#define BMP280SlaveAddressDefault (0x77)
 
 
/** A BME280 environmental sensor
A library to read environmental temperature and pressure using Bosch BME280. */
 
class BMP280 {
  public:
  
    enum {
      // The default I2C slave BusAddress.
      SlaveAddress = BMP280SlaveAddressDefault
    };
 
    /* Creates a BME280 instance connected to the I2C pins and BusAddress.
     *
     * @param i2c_obj I2C object (instance)
     * @param SlaveAddress (option) I2C-bus BusAddress (default: 0x77)
     */
    BMP280(I2C &Bus, char SlaveAddress = BMP280SlaveAddressDefault);
 
    /* Initializa BME280 sensor
    Configure sensor setting and read parameters for calibration */
    void Initialize();
 
    /* Read the current temperature value (degree Celsius) from BME280 sensor */
    int32_t Temperature();
 
    /* Read the current pressure value (hectopascal)from BME280 sensor */
    uint32_t Pressure();
 
    /* Read the current humidity value (humidity %) from BME280 sensor */
    //float HumidityGet();
 
private:
 
    I2C         *i2c_p;
    I2C         &Bus;
    char        BusAddress;
    uint16_t    dig_T1;
    int16_t     dig_T2, dig_T3;
    uint16_t    dig_P1;
    int16_t     dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
    uint16_t    dig_H1, dig_H3;
    int16_t     dig_H2, dig_H4, dig_H5, dig_H6;
    int32_t     t_fine;
 
};
 
#undef SlaveAddressDefault
#endif
 