/**
 * @file     err.c
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
#include "err.h"
#include "err.h"

/**
 * @brief Calculates 8-bit checksum for given data
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint8_t Calculated checksum value
 * 
 * @note This is a simple additive checksum that may not detect all errors
 *       but is computationally inexpensive.
 */
uint8_t checkSum8_Calc(uint8_t *_data, uint16_t _dataLength)
{
    uint8_t _Sum = 0x00;
    uint16_t _index = 0x00;

    for(_index = 0; _index < _dataLength; _index++)
    {
        _Sum += _data[_index];
    };

    return _Sum;
};


/**
 * @brief Calculates 16-bit checksum for given data
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint16_t Calculated checksum value
 * 
 * @note Provides better error detection than 8-bit checksum
 *       while maintaining simplicity.
 */
uint16_t checkSum16_Calc(uint8_t *_data, uint16_t _dataLength)
{
    uint16_t _Sum = 0x00;
    uint16_t _index = 0x00;

    for(_index = 0; _index < _dataLength; _index++)
    {
        _Sum += _data[_index];
    };

    return _Sum;
};


/**
 * @brief Calculates 32-bit checksum for given data
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint32_t Calculated checksum value
 * 
 * @note Provides the highest level of error detection among
 *       the simple checksum implementations.
 */
uint32_t checkSum32_Calc(uint8_t *_data, uint16_t _dataLength)
{
    uint32_t _Sum = 0x00;
    uint16_t _index = 0x00;

    for(_index = 0; _index < _dataLength; _index++)
    {
        _Sum += _data[_index];
    };

    return _Sum;
};


/**
 * @brief Reflects the bits of input data
 * @param _data Input data to be reflected
 * @param _dataBits Number of bits to reflect (8, 16, or 32)
 * @return uint32_t Bit-reflected output
 * 
 * @note Used internally for CRC calculations when input/output
 *       reflection is required by the CRC standard.
 */
uint32_t bitReflected(uint32_t _data, uint8_t _dataBits)
{
    uint32_t _temp = 0x00;
    uint8_t _index = 0x00;
    _dataBits--;

    for(_index = 0; _index <= _dataBits; _index++)
    {
        bitChange(_temp, (_dataBits-_index), bitCheck(_data, _index));
    }

    return _temp;
};


/**
 * @brief Calculates 8-bit CRC value
 * @param hcrc Pointer to CRC8 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint8_t Calculated CRC value
 * 
 * @note Implements standard CRC-8 algorithm with configurable:
 *       - Polynomial
 *       - Initial value
 *       - Input/output reflection
 *       - Final XOR
 */
uint8_t CRC8_Calc(hcrc8_T *hcrc, uint8_t *_data, uint16_t _dataLength)
{
    uint8_t _CRC = hcrc->Init;
    uint8_t _bitIndex  = 0x00;
    uint16_t _dataIndex = 0x00;
    uint8_t _dataTemp  = 0x00;

    for(_dataIndex = 0; _dataIndex < _dataLength; _dataIndex++)
    {
        _dataTemp = _data[_dataIndex];
        if(hcrc->refIn)
        {
           _dataTemp = (uint8_t) bitReflected(_dataTemp, 8);
        }

        _CRC ^= _dataTemp;

        for(_bitIndex = 0; _bitIndex < 8; _bitIndex++)
        {
            if(bitCheckHigh(_CRC, 7))
            {
                bitShiftLeft(_CRC, 1);
                _CRC ^= hcrc->Poly;
            }
            else
            {
                bitShiftLeft(_CRC, 1);
            };
        };
    };

    _CRC ^= hcrc->xorOut;  
    if(hcrc->refOut)
    {
        _CRC = (uint8_t) bitReflected(_CRC, 8);
    }

    return _CRC;
};


/**
 * @brief Calculates 16-bit CRC value
 * @param hcrc Pointer to CRC8 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint16_t Calculated CRC value
 * 
 * @note Implements standard CRC-16 algorithm with configurable:
 *       - Polynomial
 *       - Initial value
 *       - Input/output reflection
 *       - Final XOR
 */
uint16_t CRC16_Calc(hcrc16_T *hcrc, uint8_t *_data, uint16_t _dataLength)
{
    uint16_t _CRC = hcrc->Init;
    uint16_t _bitIndex  = 0x00;
    uint16_t _dataIndex = 0x00;
    uint8_t _dataTemp  = 0x00;

    for(_dataIndex = 0; _dataIndex < _dataLength; _dataIndex++)
    {
        _dataTemp = _data[_dataIndex];

        if(hcrc->refIn)
        {
            _dataTemp = bitReflected(_dataTemp, 8);
        };

        _CRC ^= ((uint16_t)_dataTemp<<8);

        for(_bitIndex = 0; _bitIndex < 8; _bitIndex++)
        {
            if(bitCheckHigh(_CRC, 15))
            {
                bitShiftLeft(_CRC, 1);
                _CRC ^= hcrc->Poly;
            }
            else
            {
                _CRC <<= 1;
            };
        };
    };

    _CRC ^= hcrc->xorOut; 

    if(hcrc->refOut)
    {
        _CRC = (uint16_t) bitReflected(_CRC, 16);
    };

    return _CRC;
};


/**
 * @brief Calculates 32-bit CRC value
 * @param hcrc Pointer to CRC8 configuration structure
 * @param _data Pointer to input data array
 * @param _dataLength Length of data in bytes
 * @return uint32_t Calculated CRC value
 * 
 * @note Implements standard CRC-32 algorithm with configurable:
 *       - Polynomial
 *       - Initial value
 *       - Input/output reflection
 *       - Final XOR
 */
uint32_t CRC32_Calc(hcrc32_T *hcrc, uint8_t *_data, uint16_t _dataLength)
{
    uint32_t _CRC = hcrc->Init;
    uint32_t _bitIndex  = 0x00;
    uint32_t _dataIndex = 0x00;
    uint8_t _dataTemp  = 0x00;

    for(_dataIndex = 0; _dataIndex < _dataLength; _dataIndex++)
    {
        _dataTemp = _data[_dataIndex];

        if(hcrc->refIn)
        {
            _dataTemp = bitReflected(_dataTemp, 8);
        };

        _CRC ^= ((uint32_t)_dataTemp)<<24;

        for(_bitIndex = 0; _bitIndex < 8; _bitIndex++)
        {
            if(bitCheckHigh(_CRC, 31))
            {
                bitShiftLeft(_CRC, 1);
                _CRC ^= hcrc->Poly;
            }
            else
            {
                _CRC <<= 1;
            };
        };
    };

    _CRC ^= hcrc->xorOut; 

    if(hcrc->refOut)
    {
        _CRC = (uint32_t) bitReflected(_CRC, 32);
    };

    return _CRC;
};
