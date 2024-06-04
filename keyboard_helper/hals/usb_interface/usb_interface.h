#include "keyboard_helper/hals/usb_interface/tusb/usb_descriptors.h"
#include "keyboard_helper/hals/usb_interface/tusb/usb_descriptors.c"
#include <pico/stdio.h>
#include <pico/cyw43_arch.h>

enum
{
    BLINK_REPORT = 50,
    BLINK_NOT_MOUNTED = 500,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 5000,

};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
    static uint32_t start_ms = 0;
    static bool led_state = false;

    // blink is disabled
    if (!blink_interval_ms)
        return;

    // Blink every interval ms
    if (to_ms_since_boot(get_absolute_time()) - start_ms < blink_interval_ms)
        return; // not enough time
    start_ms += blink_interval_ms;

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);
    led_state = 1 - led_state; // toggle
}

// Invoked when received SET_PROTOCOL request
// protocol is either HID_PROTOCOL_BOOT (0) or HID_PROTOCOL_REPORT (1)
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol)
{
    blink_interval_ms = BLINK_REPORT;
    (void)instance;
    (void)protocol;

    // nothing to do since we use the same compatible boot report for both Boot and Report mode.
    // TODO set a indicator for user
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
    blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
    blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
    blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
    (void)report_id;

    // keyboard interface
    if (instance == ITF_NUM_KEYBOARD)
    {
        // Set keyboard LED e.g Capslock, Numlock etc...
        if (report_type == HID_REPORT_TYPE_OUTPUT)
        {
            // bufsize should be (at least) 1
            if (bufsize < 1)
                return;

            uint8_t const kbd_leds = buffer[0];

            if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
            {
                // Capslock On: disable blink, turn led on
                blink_interval_ms = 0;
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            }
            else
            {
                // Caplocks Off: back to normal blink
                cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
                // blink_interval_ms = BLINK_MOUNTED;
            }
        }
    }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const *report, uint16_t len)
{
    (void)instance;
    (void)report;
    (void)len;

    // nothing to do
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

typedef struct TU_ATTR_PACKED
{
    uint8_t modifier;    /**< Keyboard modifier (KEYBOARD_MODIFIER_* masks). */
    uint8_t reserved;    /**< Reserved for OEM use, always set to 0. */
    uint8_t keycode[10]; /**< Key codes of the currently pressed keys. */
} hid_keyboard_report_protocol_report;

void send_report_protocol_report(uint8_t modifiers, uint8_t *keycodes, uint8_t size)
{
    hid_keyboard_report_protocol_report report;
    report.reserved = 0;
    report.modifier = modifiers;

    uint8_t keys[10] = {HID_KEY_NONE};
    for (uint8_t i = 0; i < size; i++)
    {
        if (i == 10)
        {
            break;
        }
        keys[i] = keycodes[i];
    }
    memcpy(report.keycode, keys, 10);
    tud_hid_n_report(ITF_NUM_KEYBOARD, 0, &report, sizeof(report));
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
    // Poll every 10ms
    const uint32_t interval_ms = 500;
    static uint32_t start_ms = 0;

    if (to_ms_since_boot(get_absolute_time()) - start_ms < interval_ms)
        return; // not enough time
    start_ms += interval_ms;

    uint32_t const btn = true;

    if (tud_suspended() && btn)
    {
        // Wake up host if we are in suspend mode
        // and REMOTE_WAKEUP feature is enabled by host
        tud_remote_wakeup();
    }
    else
    {
        // keyboard interface
        if (tud_hid_n_ready(ITF_NUM_KEYBOARD))
        {
            // used to avoid send multiple consecutive zero report for keyboard

            uint8_t const report_id = 0;
            uint8_t const modifier = 0;

            if (btn)
            {
                uint8_t keycode[10] = {
                    HID_KEY_0,
                    HID_KEY_1,
                    HID_KEY_2,
                    HID_KEY_3,
                    HID_KEY_4,
                    HID_KEY_5,
                    HID_KEY_6,
                    HID_KEY_7,
                    HID_KEY_8,
                    HID_KEY_9,
                };
                send_report_protocol_report(modifier, keycode, sizeof(keycode));
            }
        }
    }
}
