# 🚀 **RISC-V Arduino Porting Roadmap**  

## ✅ **Completed Work:**  
✔️ **Modified `platform.txt`** – ✅ **Dynamic linker path updated**  
✔️ **Created new chip directory (`variants/<your-chip>/`)**  
   - `variant.h` (still needs modifications)  
   - `linker_scripts/` (✅ Modified)  
   - `openocd/` (✅ Done)  
✔️ **Updated I2C driver in `Wire.cpp` and `Wire.h`**  
✔️ **Added our linker script (`linker_scripts/link.ld`)**  
✔️ **Updated startup code (`start.s`)**  
   - Corrected RISC-V vector table and initialization  
✔️ **Implemented `HardwareSerial.cpp/.h` (UART TX/RX) - Needs Verification**  

---

## 🔥 **Next Steps / To-Do List**  

### **1️⃣ Verify UART, I2C, and Syscalls**  
🔲 **Test and Debug `HardwareSerial.cpp/.h` (UART TX/RX)**  
   - Check if `Serial.begin()`, `Serial.print()`, and `Serial.read()` work correctly  
   - Ensure proper TX/RX functionality  

🔲 **Verify I2C Communication (`Wire.cpp/.h`)**  
   - Test `Wire.begin()` and communication with an I2C device  

🔲 **Fix and Test `syscalls.c` (Low-Level I/O)**  
   - Verify `_write()` → Should output UART for `printf`, `Serial.print()`  
   - Check `_read()`, `_close()`, `_fstat()`, `_sbrk()` for memory allocation  

🔲 **Verify Core Libraries (`Print.h`, `String.h`, `Stream.h`)**  
   - Ensure proper functionality of print streams and string manipulation  
   - Check compatibility with `Serial`, `Wire`, and other output classes  

---

### **2️⃣ Modify Core & Peripheral Support**  
🔲 **Update `variant.h`**  
   - Define correct pin mappings, timers, ADC, PWM settings  
   - Map UART, I2C, SPI to correct hardware peripherals  

🔲 **Modify `wiring.c` and `wiring_digital.c`**  
   - Ensure `pinMode()`, `digitalWrite()`, `analogRead()` work correctly  

🔲 **Verify `SPI` Support**  
   - Modify `SPIClass` to work with your RISC-V chip  

🔲 **Ensure `millis()`, `micros()`, `delay()` work**  
   - Implement timer-based functions correctly  

---

### **3️⃣ Toolchain & Build System Fixes**  
✔️ **Fixed dynamic linker path in `platform.txt`**  
🔲 **Ensure OpenOCD integration for flashing**  
   - Check `tools.flashrom.upload.pattern` in `platform.txt`  

🔲 **Verify full compilation & linking in Arduino IDE**  

---

### **4️⃣ Testing & Debugging**  
🔲 **Run Basic Arduino Sketches**  
   - Blink LED (`pinMode`, `digitalWrite`)  
   - Serial Print (`Serial.begin`, `Serial.print`)  
   - I2C device scan (`Wire.begin`)  

🔲 **Debug startup issues, optimize boot time**  

---

### 📌 **Immediate Next Steps**  
1️⃣ **Test UART TX/RX (`Serial.print()`, `Serial.read()`)**  
2️⃣ **Test I2C (`Wire.begin()`, scan for devices)**  
3️⃣ **Verify `syscalls.c` and ensure `_write()` works for printf**  
4️⃣ **Check compatibility of `Print.h`, `String.h`, and `Stream.h`**  

---
removed canmsg and related stuff commented Saferingbuffer