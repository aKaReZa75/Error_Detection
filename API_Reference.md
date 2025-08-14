# Error Detection Library for Embedded Systems

This section provides detailed descriptions of the checksum and CRC functions for data integrity verification in embedded systems. The library supports 8/16/32-bit checksums and configurable CRC calculations for robust error detection in communication protocols and data storage applications.

> [!NOTE]  
> The library and all of its APIs provided below have been developed by myself.  
> This library utilizes various macros defined in the `aKaReZa.h` header file for bitwise operations and register manipulations.  
> Detailed descriptions of these macros can be found at:  
> [https://github.com/aKaReZa75/AVR/blob/main/Macros.md](https://github.com/aKaReZa75/AVR/blob/main/Macros.md)  

| Feature                | Supported Variants                          |
|------------------------|--------------------------------------------|
| **Checksum**           | 8-bit, 16-bit, 32-bit                      |
| **CRC**                | CRC-8, CRC-16, CRC-32                      |
| **Configuration**      | Custom polynomials, initial values         |
| **Data Reflection**    | Input/Output reflection support            |
| **Final XOR**          | Configurable output inversion              |

## Checksum Calculations

### 8-bit Checksum
```c
uint8_t checkSum8_Calc(uint8_t *_data, uint16_t _dataLength);
```
* Simple additive checksum (modulo 256)
* @param `_data`: Pointer to data buffer
* @param `_dataLength`: Length of data in bytes
* @return 8-bit checksum value

**Example:**
```c
uint8_t data[] = {0x01, 0x02, 0x03};
uint8_t checksum = checkSum8_Calc(data, sizeof(data));
```

### 16-bit Checksum
```c
uint16_t checkSum16_Calc(uint8_t *_data, uint16_t _dataLength);
```
* Simple additive checksum (modulo 65536)
* @param `_data`: Pointer to data buffer
* @param `_dataLength`: Length of data in bytes
* @return 16-bit checksum value

### 32-bit Checksum
```c
uint32_t checkSum32_Calc(uint8_t *_data, uint16_t _dataLength);
```
* Simple additive checksum (modulo 2³²)
* @param `_data`: Pointer to data buffer
* @param `_dataLength`: Length of data in bytes
* @return 32-bit checksum value

## CRC Calculations

### CRC Configuration Structures
```c
typedef struct 
{
  uint8_t Poly;    // CRC polynomial
  uint8_t Init;    // Initial value
  bool refIn;      // Input reflection
  bool refOut;     // Output reflection
  uint8_t xorOut;  // Final XOR value
} hcrc8_T;

// Similar structures exist for hcrc16_T and hcrc32_T
```

### CRC-8 Calculation
```c
uint8_t CRC8_Calc(hcrc8_T *hcrc, uint8_t *_data, uint16_t _dataLength);
```
* Calculates 8-bit CRC with configurable parameters
* Supports common standards (CRC-8, CRC-8/MAXIM, etc.)
* @param `hcrc`: Pointer to CRC configuration
* @param `_data`: Pointer to data buffer
* @param `_dataLength`: Length of data in bytes
* @return 8-bit CRC value

**Example Configuration (CRC-8/MAXIM):**
```c
hcrc8_T crc8_config = 
{
  .Poly = 0x31,   // Polynomial x⁸ + x⁵ + x⁴ + 1
  .Init = 0x00,   // Initial value
  .refIn = true,  // Input reflection
  .refOut = true, // Output reflection
  .xorOut = 0x00  // Final XOR
};
```

### CRC-16 Calculation
```c
uint16_t CRC16_Calc(hcrc16_T *hcrc, uint8_t *_data, uint16_t _dataLength);
```
* Calculates 16-bit CRC with configurable parameters
* Supports common standards (CRC-16/CCITT, CRC-16/MODBUS, etc.)

### CRC-32 Calculation
```c
uint32_t CRC32_Calc(hcrc32_T *hcrc, uint8_t *_data, uint16_t _dataLength);
```
* Calculates 32-bit CRC with configurable parameters
* Supports common standards (CRC-32, CRC-32C, etc.)

## Complete Example
```c
#include "aKaReZa.h"
#include "err.h"

// CRC-16/CCITT configuration
hcrc16_T crc16_config = 
{
  .Poly = 0x1021,
  .Init = 0xFFFF,
  .refIn = false,
  .refOut = false,
  .xorOut = 0x0000
};

int main(void) 
{
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
    
    // Calculate checksums
    uint8_t sum8 = checkSum8_Calc(data, sizeof(data));
    uint16_t sum16 = checkSum16_Calc(data, sizeof(data));
    
    // Calculate CRC
    uint16_t crc = CRC16_Calc(&crc16_config, data, sizeof(data));
    
    while(1);
}
```

## Summary Table
| API Function         | Description                                   |
|----------------------|-----------------------------------------------|
| `checkSum8_Calc`     | Calculates 8-bit simple checksum              |
| `checkSum16_Calc`    | Calculates 16-bit simple checksum             |
| `checkSum32_Calc`    | Calculates 32-bit simple checksum             |
| `CRC8_Calc`          | Calculates 8-bit CRC with configuration       |
| `CRC16_Calc`         | Calculates 16-bit CRC with configuration     |
| `CRC32_Calc`         | Calculates 32-bit CRC with configuration     |

> [!IMPORTANT]
> 1. For CRC calculations, ensure proper configuration of polynomial, initial value, and reflection settings
> 2. Checksums provide basic error detection while CRCs offer stronger protection
> 3. Reflection settings must match the target protocol specifications
> 4. Pre-configured structures for common CRC standards are recommended


# 🌟 Support Me
If you found this repository useful:
- Subscribe to my [YouTube Channel](https://www.youtube.com/@aKaReZa75).
- Share this repository with others.
- Give this repository and my other repositories a star.
- Follow my [GitHub account](https://github.com/aKaReZa75).

# ✉️ Contact Me
Feel free to reach out to me through any of the following platforms:
- 📧 [Email: aKaReZa75@gmail.com](mailto:aKaReZa75@gmail.com)
- 🎥 [YouTube: @aKaReZa75](https://www.youtube.com/@aKaReZa75)
- 💼 [LinkedIn: @akareza75](https://www.linkedin.com/in/akareza75)
