/*
Copyright 2022 Huckies <https://github.com/Huckies>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "eeprom_driver.h"
#include "platform_deps.h"
#include "gpio.h"

void bootmagic_lite_reset_eeprom(void)
{
    eeprom_driver_erase();
}

void bootloader_boot_mode_set(uint8_t mode)
{
    if (mode != BOOTLOADER_BOOT_MODE_IAP && mode != BOOTLOADER_BOOT_MODE_USB &&
        mode != BOOTLOADER_BOOT_MODE_BLE && mode != BOOTLOADER_BOOT_MODE_ESB) {
        PRINT("Invalid mode select, will ignore.\n");
        return;
    }
    if (0
#ifndef USB_ENABLE
        || (mode == BOOTLOADER_BOOT_MODE_USB)
#endif
#ifndef BLE_ENABLE
        || (mode == BOOTLOADER_BOOT_MODE_BLE)
#endif
#ifndef ESB_ENABLE
        || (mode == BOOTLOADER_BOOT_MODE_ESB)
#endif
    ) {
        PRINT("Mode %d is not enabled, will ignore.\n", mode);
        return;
    }

    uint8_t buffer[EEPROM_PAGE_SIZE], ret;

    do {
        ret = EEPROM_READ(QMK_EEPROM_RESERVED_START_POSITION, &buffer, sizeof(buffer));
    } while (ret);
    buffer[0] = mode;
    do {
        ret = EEPROM_ERASE(QMK_EEPROM_RESERVED_START_POSITION, EEPROM_PAGE_SIZE) ||
              EEPROM_WRITE(QMK_EEPROM_RESERVED_START_POSITION, buffer, EEPROM_PAGE_SIZE);
    } while (ret);
}

uint8_t bootloader_boot_mode_get()
{
    uint8_t buffer, ret;

    do {
        ret = EEPROM_READ(QMK_EEPROM_RESERVED_START_POSITION, &buffer, sizeof(buffer));
    } while (ret);
    if (buffer == BOOTLOADER_BOOT_MODE_IAP || buffer == BOOTLOADER_BOOT_MODE_USB ||
        buffer == BOOTLOADER_BOOT_MODE_BLE || buffer == BOOTLOADER_BOOT_MODE_ESB) {
        return buffer;
    } else {
        return bootloader_set_to_default_mode("Invalid boot mode");
    }
}

void bootloader_select_boot_mode()
{
    uint8_t mode = bootloader_boot_mode_get();

    if (mode == BOOTLOADER_BOOT_MODE_IAP) {
        mode = bootloader_set_to_default_mode("Successfully booted from IAP");
    } else if (mode == BOOTLOADER_BOOT_MODE_USB) {
#ifdef POWER_DETECT_PIN
        if (!readPin(POWER_DETECT_PIN)) {
            bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_BLE);
            mode = BOOTLOADER_BOOT_MODE_BLE;
            PRINT("Cable not connected, USB mode is disabled.\n");
        }
#endif
    }

    //! TODO: for test only!
    // mode = BOOTLOADER_BOOT_MODE_BLE;

    switch (mode) {
#ifdef USB_ENABLE
        case BOOTLOADER_BOOT_MODE_USB:
            // cable mode
            kbd_protocol_type = kbd_protocol_usb;
            break;
#endif
#ifdef BLE_ENABLE
        case BOOTLOADER_BOOT_MODE_BLE:
            // bluetooth mode
            kbd_protocol_type = kbd_protocol_ble;
            break;
#endif
#ifdef ESB_ENABLE
        case BOOTLOADER_BOOT_MODE_ESB:
            // 2.4g mode
            kbd_protocol_type = kbd_protocol_esb;
            break;
#endif
        default:
            PRINT("Invalid mode record detected, ");
            if (mode == BOOTLOADER_BOOT_MODE_IAP) {
                PRINT("will reside in IAP.\n");
            } else {
                bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_IAP);
                mode = bootloader_boot_mode_get();
                PRINT("set to IAP... %s\n", mode == BOOTLOADER_BOOT_MODE_IAP ? "done" : "fail");
            }
            PRINT("Reboot execute.\n");
            WAIT_FOR_DBG;
            SYS_ResetExecute();
    }
}

uint8_t bootloader_set_to_default_mode(const char *reason)
{
    bool limited_mode = false;

#ifdef POWER_DETECT_PIN
    if (!readPin(POWER_DETECT_PIN)) {
        // cable not connected, skip usb mode
        limited_mode = true;
    }
#endif
    PRINT("%s, ", reason);
#ifdef USB_ENABLE
    if (!limited_mode) {
        PRINT("default to USB.\n");
        bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_USB);
        return BOOTLOADER_BOOT_MODE_USB;
    }
#elif defined BLE_ENABLE
    PRINT("default to BLE slot 0.\n");
    bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_BLE);
    return BOOTLOADER_BOOT_MODE_BLE;
#else
    PRINT("default to ESB.\n");
    bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_ESB);
    return BOOTLOADER_BOOT_MODE_ESB;
#endif
    __builtin_unreachable();
}

void bootloader_jump()
{
    PRINT("Jumping IAP...\n");
    bootloader_boot_mode_set(BOOTLOADER_BOOT_MODE_IAP);
    if (bootloader_boot_mode_get() == BOOTLOADER_BOOT_MODE_IAP) {
        PRINT("Boot mode set to IAP.\n");
        mcu_reset();
    } else {
        PRINT("Setting boot mode failed, abort.\n");
    }
}

void mcu_reset()
{
#if __BUILDING_APP__
#ifdef USB_ENABLE
    if (kbd_protocol_type == kbd_protocol_usb) {
        platform_reboot_usb();
    }
#endif
#ifdef BLE_ENABLE
    if (kbd_protocol_type == kbd_protocol_ble) {
        platform_reboot_ble();
    }
#endif
#ifdef ESB_ENABLE
    if (kbd_protocol_type == kbd_protocol_esb) {
        platform_reboot_esb();
    }
#endif
#endif
#if __BUILDING_IAP__
    SYS_ResetExecute();
#endif
}
