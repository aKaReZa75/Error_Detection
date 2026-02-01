## 📦 CRC Standards Reference

This document outlines commonly used CRC algorithms across 8-bit, 16-bit, and 32-bit variants. Each section includes a description of the CRC type, its standard parameters, a configuration structure compatible with the error detection library, and its practical application in embedded systems.

> [!NOTE]  
> These CRC configurations are compatible with the `hcrc8_T`, `hcrc16_T`, and `hcrc32_T` structures defined in the `err.h` file.  

---

### 🔹 CRC-8 Variants

#### CRC-8/MAXIM
- **Used In**: Maxim/Dallas 1-Wire devices (e.g., DS18B20 temperature sensor)
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

#### CRC-8/NRSC-5
- **Used In**: AHT20 temperature and humidity sensor
- **Purpose**: Validates sensor data integrity during I²C communication
- **Configuration**:
```c
hcrc8_T crc8_aht20 = 
{
  .Poly = 0x31, // x⁸ + x⁵ + x⁴ + 1
  .Init = 0xFF,
  .refIn = false,
  .refOut = false,
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

#### CRC-8/SAE-J1850
* **Used In**: Automotive protocols (e.g., SAE J1850, CAN-related checks)
* **Purpose**: Ensures integrity of automotive communication frames
* **Configuration**:
```c
hcrc8_T crc8_sae_j1850 = 
{
  .Poly   = 0x1D, // x⁸ + x⁴ + x³ + x² + 1
  .Init   = 0xFF,
  .refIn  = false,
  .refOut = false,
  .xorOut = 0xFF
};
```

#### CRC-8/AUTOSAR
* **Used In**: AUTOSAR automotive standard (E2E protection)
* **Purpose**: End-to-end communication protection in automotive ECUs
* **Configuration**:
```c
hcrc8_T crc8_autosar = 
{
  .Poly   = 0x2F, // x⁸ + x⁵ + x³ + x² + x + 1
  .Init   = 0xFF,
  .refIn  = false,
  .refOut = false,
  .xorOut = 0xFF
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

#### CRC-32/AUTOSAR
- **Used In**: AUTOSAR automotive standard (E2E protection, 32-bit variant)
- **Purpose**: Enhanced integrity protection for safety-critical automotive applications
- **Configuration**:
```c
hcrc32_T crc32_autosar = 
{
  .Poly = 0xF4ACFB13, // AUTOSAR polynomial
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

> [!IMPORTANT]
> All configurations assume little-endian byte order. For big-endian systems, additional byte swapping may be required.

## 📑 Reference Table

| Standard                 | Polynomial | Init Value | RefIn | RefOut | XorOut     | Typical Applications            |
| ------------------------ | ---------- | ---------- | ----- | ------ | ---------- | ------------------------------- |
| **CRC-8/MAXIM**          | 0x31       | 0x00       | true  | true   | 0x00       | Maxim/Dallas 1-Wire (DS18B20)   |
| **CRC-8/NRSC-5**         | 0x31       | 0xFF       | false | false  | 0x00       | AHT20 temperature/humidity      |
| **CRC-8/ATM**            | 0x07       | 0x00       | false | false  | 0x00       | ATM networks, lightweight proto |
| **CRC-8/SAE-J1850**      | 0x1D       | 0xFF       | false | false  | 0xFF       | Automotive (SAE J1850 frames)   |
| **CRC-8/AUTOSAR**        | 0x2F       | 0xFF       | false | false  | 0xFF       | AUTOSAR E2E automotive ECUs     |
| **CRC-16/MODBUS**        | 0x8005     | 0xFFFF     | true  | true   | 0x0000     | MODBUS RTU industrial control   |
| **CRC-16/CCITT-FALSE**   | 0x1021     | 0xFFFF     | false | false  | 0x0000     | X.25, HDLC, Bluetooth           |
| **CRC-32 (Ethernet)**    | 0x04C11DB7 | 0xFFFFFFFF | true  | true   | 0xFFFFFFFF | Ethernet, ZIP, PNG, file checks |
| **CRC-32C (Castagnoli)** | 0x1EDC6F41 | 0xFFFFFFFF | true  | true   | 0xFFFFFFFF | iSCSI, SATA, Btrfs, storage sys |
| **CRC-32/AUTOSAR**       | 0xF4ACFB13 | 0xFFFFFFFF | true  | true   | 0xFFFFFFFF | AUTOSAR E2E safety-critical sys |


> [!NOTE]
> **Residue in CRC Algorithms**
>
> The **Residue** is the expected remainder when a CRC calculation is applied to the entire data block **including its CRC checksum**.
>
> * In many CRC definitions, the Residue is defined to be **0**. This is called the **zero-check property**, because when the receiver re-calculates the CRC over `(Message + CRC)`, the result will be zero—indicating that the message is valid and error-free.
>
> * However, not all CRC algorithms use zero as their Residue. Some standards define a **non-zero constant Residue** instead. For example:
>
>   * **CRC-32 (Ethernet)** has a Residue of `0xDEBB20E3`.
>   * **CRC-16/CCITT-FALSE** has a Residue of `0x1D0F`.
>
> * This behavior depends on the **Init value**, **XorOut**, and reflection settings (`refIn`, `refOut`). These parameters affect whether the Residue ends up being `0` or some other fixed constant.
>
> * The Residue is very important when validating an implementation:
>
>   1. If your computed CRC appended to the data produces the defined Residue, your CRC function is correct.
>   2. If you always expect `0` but the algorithm defines a different Residue, your validation test will fail.

✅ In short:
 * **Residue = 0** → zero-check property (common in lightweight CRCs like CRC-8/MAXIM or CRC-16/MODBUS).
 * **Residue = constant (≠ 0)** → defined by standard, must be checked against that value (common in telecom and file integrity CRCs).

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
