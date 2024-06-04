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
