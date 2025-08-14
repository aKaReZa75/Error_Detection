/**
 * @file     err.h
 * @brief    Error Detection Library (Checksum & CRC) for Embedded Systems
 * @note     This library provides functions for various error detection methods including
 *           8/16/32-bit Checksum and CRC calculations. Suitable for communication protocols
 *           and data integrity verification.
 * 
 * @author   Hossein Bagheri
 * @github   https://github.com/aKaReZa75
 * 
 * @note     For detailed explanations, usage examples, and implementation notes,
 *           please visit the repository:
 *           https://github.com/aKaReZa75/Error_Detection
 */

#ifndef _err_H_
#define _err_H_

#include "aKaReZa.h"

/**
 * @brief CRC8 configuration structure
 * @details Contains all parameters needed to configure CRC8 calculation
 */
typedef struct 
{
  uint8_t Poly;    ///< Polynomial value for CRC8 calculation
  uint8_t Init;    ///< Initial value for CRC8 calculation
  bool refIn;      ///< Input data reflection (true/false)
  bool refOut;     ///< Output data reflection (true/false)
  uint8_t xorOut;  ///< Final XOR value for CRC8 result
} hcrc8_T;

/**
 * @brief CRC16 configuration structure
 * @details Contains all parameters needed to configure CRC16 calculation
 */
typedef struct 
{
  uint16_t Poly;    ///< Polynomial value for CRC16 calculation
  uint16_t Init;    ///< Initial value for CRC16 calculation
  bool refIn;       ///< Input data reflection (true/false)
  bool refOut;      ///< Output data reflection (true/false)
  uint16_t xorOut;  ///< Final XOR value for CRC16 result
} hcrc16_T;

/**
 * @brief CRC32 configuration structure
 * @details Contains all parameters needed to configure CRC32 calculation
 */
typedef struct 
{
  uint32_t Poly;    ///< Polynomial value for CRC32 calculation
  uint32_t Init;    ///< Initial value for CRC32 calculation
  bool refIn;       ///< Input data reflection (true/false)
  bool refOut;      ///< Output data reflection (true/false)
  uint32_t xorOut;  ///< Final XOR value for CRC32 result
} hcrc32_T;

/**
 * @brief Calculate 8-bit checksum
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint8_t Calculated 8-bit checksum value
 */
uint8_t checkSum8_Calc(uint8_t *_data, uint16_t _dataLength);

/**
 * @brief Calculate 16-bit checksum
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint16_t Calculated 16-bit checksum value
 */
uint16_t checkSum16_Calc(uint8_t *_data, uint16_t _dataLength);

/**
 * @brief Calculate 32-bit checksum
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint32_t Calculated 32-bit checksum value
 */
uint32_t checkSum32_Calc(uint8_t *_data, uint16_t _dataLength);

/**
 * @brief Calculate 8-bit CRC value
 * @param hcrc Pointer to CRC8 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint8_t Calculated 8-bit CRC value
 */
uint8_t CRC8_Calc(hcrc8_T *hcrc, uint8_t *_data, uint16_t _dataLength);

/**
 * @brief Calculate 16-bit CRC value
 * @param hcrc Pointer to CRC16 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint16_t Calculated 16-bit CRC value
 */
uint16_t CRC16_Calc(hcrc16_T *hcrc, uint8_t *_data, uint16_t _dataLength);

/**
 * @brief Calculate 32-bit CRC value
 * @param hcrc Pointer to CRC32 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint32_t Calculated 32-bit CRC value
 */
uint32_t CRC32_Calc(hcrc32_T *hcrc, uint8_t *_data, uint16_t _dataLength);

#endif