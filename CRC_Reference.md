## 📦 CRC Standards Reference

This document outlines commonly used CRC algorithms across 8-bit, 16-bit, and 32-bit variants. Each section includes a description of the CRC type, its standard parameters, a configuration structure compatible with the error detection library, and its practical application in embedded systems.

> [!NOTE]  
> These CRC configurations are compatible with the `hcrc8_T`, `hcrc16_T`, and `hcrc32_T` structures defined in the `err.h` file.  

---

### 🔹 CRC-8 Variants

#### CRC-8/MAXIM
- **Used In**: Maxim/Dallas 1-Wire devices (e.g., DS18B20 temperature & AHT20 sensor)
- **Purpose**: Verifies short data packets in low-speed serial protocols
- **Configuration**:
```c
hcrc8_T crc8_maxim = 
{
  .Poly = 0x31, // x⁸ + x⁵ + x⁴ + 1
  .Init = 0x00,
  .refIn = true,
  .refOut = true,
  .xorOut = 0x00
};
```

#### CRC-8/ATM
- **Used In**: ATM networks, basic embedded protocols
- **Purpose**: Lightweight error detection for small data blocks
- **Configuration**:
```c
hcrc8_T crc8_atm = 
{
  .Poly = 0x07, // x⁸ + x² + x + 1
  .Init = 0x00,
  .refIn = false,
  .refOut = false,
  .xorOut = 0x00
};
```

---

### 🔸 CRC-16 Variants

#### CRC-16/MODBUS
- **Used In**: MODBUS RTU communication protocol
- **Purpose**: Ensures integrity of industrial control messages
- **Configuration**:
```c
hcrc16_T crc16_modbus = 
{
  .Poly = 0x8005, // x¹⁶ + x¹⁵ + x² + 1
  .Init = 0xFFFF,
  .refIn = true,
  .refOut = true,
  .xorOut = 0x0000
};
```

#### CRC-16/CCITT-FALSE
- **Used In**: X.25, HDLC, Bluetooth, and many telecom protocols
- **Purpose**: Reliable error detection for medium-sized data frames
- **Configuration**:
```c
hcrc16_T crc16_ccitt_false = 
{
  .Poly = 0x1021, // x¹⁶ + x¹² + x⁵ + 1
  .Init = 0xFFFF,
  .refIn = false,
  .refOut = false,
  .xorOut = 0x0000
};
```

---

### 🔷 CRC-32 Variants

#### CRC-32 (Standard Ethernet)
- **Used In**: Ethernet, ZIP files, PNG images, and many file formats
- **Purpose**: High-integrity verification for large data blocks
- **Configuration**:
```c
hcrc32_T crc32_standard = 
{
  .Poly = 0x04C11DB7, // x³² + x²⁶ + x²³ + ... + x² + x + 1
  .Init = 0xFFFFFFFF,
  .refIn = true,
  .refOut = true,
  .xorOut = 0xFFFFFFFF
};
```

#### CRC-32C (Castagnoli)
- **Used In**: iSCSI, SATA, Btrfs, and other high-performance storage systems
- **Purpose**: Optimized for hardware acceleration and strong error detection
- **Configuration**:
```c
hcrc32_T crc32_castagnoli = 
{
  .Poly = 0x1EDC6F41, // Optimized for error detection
  .Init = 0xFFFFFFFF,
  .refIn = true,
  .refOut = true,
  .xorOut = 0xFFFFFFFF
};
```

---

### 📌 Notes
- CRC-8 is ideal for sensors and small packets.
- CRC-16 is widely used in industrial and telecom protocols.
- CRC-32 is preferred for file integrity and high-throughput systems.
- Always match CRC settings to the target protocol or device datasheet.
- Use reflection and XOR settings carefully—they affect compatibility.

## Reference Table

| Standard       | Polynomial | Initial Value | RefIn | RefOut | XorOut | Applications         |
|----------------|------------|---------------|-------|--------|--------|----------------------|
| CRC-8/MAXIM    | 0x31       | 0x00          | true  | true   | 0x00   | 1-Wire, AHT20       |
| CRC-16/MODBUS  | 0x8005     | 0xFFFF        | true  | true   | 0x0000 | MODBUS RTU          |
| CRC-16/CCITT   | 0x1021     | 0x0000        | false | false  | 0x0000 | XMODEM, Bluetooth   |
| CRC-32         | 0x04C11DB7 | 0xFFFFFFFF    | true  | true   | 0xFFFFFFFF | Ethernet, ZIP     |
| CRC-32C        | 0x1EDC6F41 | 0xFFFFFFFF    | true  | true   | 0xFFFFFFFF | SCTP, ext4       |

> [!NOTE]
> All configurations assume little-endian byte order. For big-endian systems, additional byte swapping may be required.


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
