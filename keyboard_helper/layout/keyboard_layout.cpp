#include <gpio.h>
#include "pico/stdlib.h"

class KeyboardLayout
{
protected:
    // layout variable
    bool layout[3][12];

    // private constructor
    KeyboardLayout() = default;

    // function to read all the column values
    bool *readColumns()
    {
        bool values[12];
        values[0] = gpio_get(COLUMN_1);
        values[1] = gpio_get(COLUMN_2);
        values[2] = gpio_get(COLUMN_3);
        values[3] = gpio_get(COLUMN_4);
        values[4] = gpio_get(COLUMN_5);
        values[5] = gpio_get(COLUMN_6);
        values[6] = gpio_get(COLUMN_7);
        values[7] = gpio_get(COLUMN_8);
        values[8] = gpio_get(COLUMN_9);
        values[9] = gpio_get(COLUMN_10);
        values[10] = gpio_get(COLUMN_11);
        values[11] = gpio_get(COLUMN_12);
        return values;
    }

public:
    static void init()
    {
        //     gpio_init(20);
        //     gpio_set_dir(20, GPIO_OUT);

        // innitiating the gpio
        gpio_init(COLUMN_1);
        gpio_init(COLUMN_2);
        gpio_init(COLUMN_3);
        gpio_init(COLUMN_4);
        gpio_init(COLUMN_5);
        gpio_init(COLUMN_6);
        gpio_init(COLUMN_7);
        gpio_init(COLUMN_8);
        gpio_init(COLUMN_9);
        gpio_init(COLUMN_10);
        gpio_init(COLUMN_11);
        gpio_init(COLUMN_12);
        gpio_init(ROW_1);
        gpio_init(ROW_2);
        gpio_init(ROW_3);
        gpio_init(RIGHT_THUMB_1);
        gpio_init(RIGHT_THUMB_2);
        gpio_init(RIGHT_THUMB_3);
        gpio_init(LEFT_THUMB_1);
        gpio_init(LEFT_THUMB_2);
        gpio_init(LEFT_THUMB_3);

        // setting directions on the pins
        gpio_set_dir(COLUMN_1, GPIO_IN);
        gpio_set_dir(COLUMN_2, GPIO_IN);
        gpio_set_dir(COLUMN_3, GPIO_IN);
        gpio_set_dir(COLUMN_4, GPIO_IN);
        gpio_set_dir(COLUMN_5, GPIO_IN);
        gpio_set_dir(COLUMN_6, GPIO_IN);
        gpio_set_dir(COLUMN_7, GPIO_IN);
        gpio_set_dir(COLUMN_8, GPIO_IN);
        gpio_set_dir(COLUMN_9, GPIO_IN);
        gpio_set_dir(COLUMN_10, GPIO_IN);
        gpio_set_dir(COLUMN_11, GPIO_IN);
        gpio_set_dir(COLUMN_12, GPIO_IN);
        gpio_set_dir(ROW_1, GPIO_OUT);
        gpio_set_dir(ROW_1, GPIO_OUT);
        gpio_set_dir(ROW_1, GPIO_OUT);
        gpio_set_dir(RIGHT_THUMB_1, GPIO_IN);
        gpio_set_dir(RIGHT_THUMB_2, GPIO_IN);
        gpio_set_dir(RIGHT_THUMB_3, GPIO_IN);
        gpio_set_dir(LEFT_THUMB_1, GPIO_IN);
        gpio_set_dir(LEFT_THUMB_2, GPIO_IN);
        gpio_set_dir(LEFT_THUMB_3, GPIO_IN);

        // setting pull up and pull down
        gpio_pull_down(COLUMN_1);
        gpio_pull_down(COLUMN_2);
        gpio_pull_down(COLUMN_3);
        gpio_pull_down(COLUMN_4);
        gpio_pull_down(COLUMN_5);
        gpio_pull_down(COLUMN_6);
        gpio_pull_down(COLUMN_7);
        gpio_pull_down(COLUMN_8);
        gpio_pull_down(COLUMN_9);
        gpio_pull_down(COLUMN_10);
        gpio_pull_down(COLUMN_11);
        gpio_pull_down(COLUMN_12);
        gpio_pull_up(RIGHT_THUMB_1);
        gpio_pull_up(RIGHT_THUMB_2);
        gpio_pull_up(RIGHT_THUMB_3);
        gpio_pull_up(LEFT_THUMB_1);
        gpio_pull_up(LEFT_THUMB_2);
        gpio_pull_up(LEFT_THUMB_3);
    }

    LayoutReadReport *scan()
    {
        // creating a LayoutReadReport object to store the data
        LayoutReadReport *layoutReport = new LayoutReadReport();

        // reading and appending the right thumb data
        bool rightThumb1 = !gpio_get(RIGHT_THUMB_1);
        bool rightThumb2 = !gpio_get(RIGHT_THUMB_2);
        bool rightThumb3 = !gpio_get(RIGHT_THUMB_3);

        layoutReport->setRightThumbs(rightThumb1, rightThumb2, rightThumb3);

        // reading and appending the left thumb data
        bool leftThumb1 = !gpio_get(LEFT_THUMB_1);
        bool leftThumb2 = !gpio_get(LEFT_THUMB_2);
        bool leftThumb3 = !gpio_get(LEFT_THUMB_3);
        layoutReport->setRightThumbs(leftThumb1, leftThumb2, leftThumb3);

        // reading the first column data
        gpio_put(ROW_1, 1);
        sleep_us(100);
        bool *row1 = readColumns();
        sleep_us(100);

        // reading the second column data
        gpio_put(ROW_2, 1);
        sleep_us(100);
        bool *row2 = readColumns();
        sleep_us(100);

        // reading the third column data
        gpio_put(ROW_3, 1);
        sleep_us(100);
        bool *row3 = readColumns();
        sleep_us(100);

        // setting the rows and column data
        layoutReport->setRows(row1, row2, row3);

        // returning a pointer to the layout report
        return layoutReport;

        // this funtion sleeps for 600us
    }

    static KeyboardLayout &getInstance()
    {
        static KeyboardLayout instance;
        return instance;
    }
    KeyboardLayout(const KeyboardLayout &) = delete;
    KeyboardLayout(KeyboardLayout &&) = delete;
    KeyboardLayout operator=(const KeyboardLayout &) = delete;
    KeyboardLayout operator=(KeyboardLayout &&) = delete;
};

class LayoutReadReport
{
private:
    bool keys[42];
    // finger keys
    bool c1_1;
    bool c1_2;
    bool c1_3;
    bool c2_1;
    bool c2_2;
    bool c2_3;
    bool c3_1;
    bool c3_2;
    bool c3_3;
    bool c4_1;
    bool c4_2;
    bool c4_3;
    bool c5_1;
    bool c5_2;
    bool c5_3;
    bool c6_1;
    bool c6_2;
    bool c6_3;
    bool c7_1;
    bool c7_2;
    bool c7_3;
    bool c8_1;
    bool c8_2;
    bool c8_3;
    bool c9_1;
    bool c9_2;
    bool c9_3;
    bool c10_1;
    bool c10_2;
    bool c10_3;
    bool c11_1;
    bool c11_2;
    bool c11_3;
    bool c12_1;
    bool c12_2;
    bool c12_3;

    // left thumb keys
    bool lt_1;
    bool lt_2;
    bool lt_3;

    // right thumb keys
    bool rt_1;
    bool rt_2;
    bool rt_3;

    KeyLocation locations[42] = {
        KeyLocation::C1_1,
        KeyLocation::C1_2,
        KeyLocation::C1_3,
        KeyLocation::C2_1,
        KeyLocation::C2_2,
        KeyLocation::C2_3,
        KeyLocation::C3_1,
        KeyLocation::C3_2,
        KeyLocation::C3_3,
        KeyLocation::C4_1,
        KeyLocation::C4_2,
        KeyLocation::C4_3,
        KeyLocation::C5_1,
        KeyLocation::C5_2,
        KeyLocation::C5_3,
        KeyLocation::C6_1,
        KeyLocation::C6_2,
        KeyLocation::C6_3,
        KeyLocation::C7_1,
        KeyLocation::C7_2,
        KeyLocation::C7_3,
        KeyLocation::C8_1,
        KeyLocation::C8_2,
        KeyLocation::C8_3,
        KeyLocation::C9_1,
        KeyLocation::C9_2,
        KeyLocation::C9_3,
        KeyLocation::C10_1,
        KeyLocation::C10_2,
        KeyLocation::C10_3,
        KeyLocation::C11_1,
        KeyLocation::C11_2,
        KeyLocation::C11_3,
        KeyLocation::C12_1,
        KeyLocation::C12_2,
        KeyLocation::C12_3,
        KeyLocation::LT_1,
        KeyLocation::LT_2,
        KeyLocation::LT_3,
        KeyLocation::RT_1,
        KeyLocation::RT_2,
        KeyLocation::RT_3,
    };

public:
    std::vector<KeyLocation> getPressedKeys()
    {
        /// returns a vector of all the pressed KeyLocations
        std::vector<KeyLocation> pressedKeys;
        for (int i = 0; i < 41; i++)
        {
            if (getKey(locations[i]))
            {
                pressedKeys.push_back(locations[i]);
            }
        }
        return pressedKeys;
    }

    bool getKey(KeyLocation key)
    {
        switch (key)
        {
        case C1_1:
            return c1_1;
            break;
        case C1_2:
            return c1_2;
            break;
        case C1_3:
            return c1_3;
            break;
        case C2_1:
            return c2_1;
            break;
        case C2_2:
            return c2_2;
            break;
        case C2_3:
            return c2_3;
            break;
        case C3_1:
            return c3_1;
            break;
        case C3_2:
            return c3_2;
            break;
        case C3_3:
            return c3_3;
            break;
        case C4_1:
            return c4_1;
            break;
        case C4_2:
            return c4_2;
            break;
        case C4_3:
            return c4_3;
            break;
        case C5_1:
            return c5_1;
            break;
        case C5_2:
            return c5_2;
            break;
        case C5_3:
            return c5_3;
            break;
        case C6_1:
            return c6_1;
            break;
        case C6_2:
            return c6_2;
            break;
        case C6_3:
            return c6_3;
            break;
        case C7_1:
            return c7_1;
            break;
        case C7_2:
            return c7_2;
            break;
        case C7_3:
            return c7_3;
            break;
        case C8_1:
            return c8_1;
            break;
        case C8_2:
            return c8_2;
            break;
        case C8_3:
            return c8_3;
            break;
        case C9_1:
            return c9_1;
            break;
        case C9_2:
            return c9_2;
            break;
        case C9_3:
            return c9_3;
            break;
        case C10_1:
            return c10_1;
            break;
        case C10_2:
            return c10_1;
            break;
        case C10_3:
            return c10_3;
            break;
        case C11_1:
            return c11_1;
            break;
        case C11_2:
            return c11_2;
            break;
        case C11_3:
            return c11_3;
            break;
        case C12_1:
            return c12_1;
            break;
        case C12_2:
            return c12_2;
            break;
        case C12_3:
            return c12_3;
            break;
        case LT_1:
            return lt_1;
            break;
        case LT_2:
            return lt_2;
            break;
        case LT_3:
            return lt_3;
            break;
        case RT_1:
            return rt_1;
            break;
        case RT_2:
            return rt_2;
            break;
        case RT_3:
            return rt_3;
            break;
        }
    }

    void setRightThumbs(bool thumb1, bool thumb2, bool thumb3)
    {
        rt_1 = thumb1;
        rt_2 = thumb2;
        rt_3 = thumb3;
    }

    void setLeftThumbs(bool thumb1, bool thumb2, bool thumb3)
    {
        lt_1 = thumb1;
        lt_2 = thumb2;
        lt_3 = thumb3;
    }

    void setRows(bool r1[12], bool r2[12], bool r3[12])
    {
        c1_1 = r1[0];
        c2_1 = r1[1];
        c3_1 = r1[2];
        c4_1 = r1[3];
        c5_1 = r1[4];
        c6_1 = r1[5];
        c7_1 = r1[6];
        c8_1 = r1[7];
        c9_1 = r1[8];
        c10_1 = r1[9];
        c11_1 = r1[10];
        c12_1 = r1[11];
        c1_2 = r2[0];
        c2_2 = r2[1];
        c3_2 = r2[2];
        c4_2 = r2[3];
        c5_2 = r2[4];
        c6_2 = r2[5];
        c7_2 = r2[6];
        c8_2 = r2[7];
        c9_2 = r2[8];
        c10_2 = r2[9];
        c11_2 = r2[10];
        c12_2 = r2[11];
        c1_3 = r3[0];
        c2_3 = r3[1];
        c3_3 = r3[2];
        c4_3 = r3[3];
        c5_3 = r3[4];
        c6_3 = r3[5];
        c7_3 = r3[6];
        c8_3 = r3[7];
        c9_3 = r3[8];
        c10_3 = r3[9];
        c11_3 = r3[10];
        c12_3 = r3[11];
    }

    //                col 1    col 2    col 3    col 4    col 5    col 6        col 7    col 8    col 9   col 10   col 11   col 12
    //
    //             +========+========+========+========+========+========+   +========+========+========+========+========+========+
    //  row 3   =  |  C1_3  |  C2_3  |  C3_3  |  C4_3  |  C5_3  |  C6_3  |   |  C7_3  |  C8_3  |  C9_3  | C10_3  | C11_3  | C12_3  |
    //             +--------+--------+--------+--------+--------+--------+   +--------+--------+--------+--------+--------+--------+
    //  row 2   =  |  C1_2  |  C2_2  |  C2_2  |  C4_2  |  C5_2  |  C6_2  |   |  C7_2  |  C8_2  |  C9_2  | C10_2  | C11_2  | C12_2  |
    //             +--------+--------+--------+--------+--------+--------+   +--------+--------+--------+--------+--------+--------+
    //  row 1   =  |  C1_1  |  C2_1  |  C3_1  |  C4_1  |  C5_1  |  C6_1  |   |  C7_1  |  C8_1  |  C9_1  | C10_1  | C11_1  | C12_1  |
    //             +========+========+========+========+========+========+   +========+========+========+========+========+========+
    //
    //                               +========+========+========+                     +========+========+========+
    //                               |  LT_1  |  LT_2  |  LT_3  |                     |  RT_1  |  RT_2  |  RT_3  |
    //                               +========+========+========+                     +========+========+========+
};

enum PinLayout
{
    // left side
    COLUMN_1 = 15,
    COLUMN_2 = 14,
    COLUMN_3 = 13,
    COLUMN_4 = 12,
    COLUMN_5 = 11,
    COLUMN_6 = 10,

    // right side
    COLUMN_7 = 21,
    COLUMN_8 = 20,
    COLUMN_9 = 19,
    COLUMN_10 = 18,
    COLUMN_11 = 17,
    COLUMN_12 = 16,

    // rows
    ROW_1 = 9,
    ROW_2 = 8,
    ROW_3 = 7,

    // right side thumb keys
    RIGHT_THUMB_1 = 0,
    RIGHT_THUMB_2 = 1,
    RIGHT_THUMB_3 = 2,

    // left side thumb keys
    LEFT_THUMB_1 = 27,
    LEFT_THUMB_2 = 26,
    LEFT_THUMB_3 = 22,

    // blutooth trigger
    BLUETOOTH_TRIGGER = 6,

    // display control
    DISPLAY_SDA = 4,
    DISPLAY_SCL = 5,

    // mode key
    MODE_KEY = 3,

    // indicator led
    LED = 28,
};

enum KeyLocation
{
    C1_1,
    C1_2,
    C1_3,
    C2_1,
    C2_2,
    C2_3,
    C3_1,
    C3_2,
    C3_3,
    C4_1,
    C4_2,
    C4_3,
    C5_1,
    C5_2,
    C5_3,
    C6_1,
    C6_2,
    C6_3,
    C7_1,
    C7_2,
    C7_3,
    C8_1,
    C8_2,
    C8_3,
    C9_1,
    C9_2,
    C9_3,
    C10_1,
    C10_2,
    C10_3,
    C11_1,
    C11_2,
    C11_3,
    C12_1,
    C12_2,
    C12_3,
    LT_1,
    LT_2,
    LT_3,
    RT_1,
    RT_2,
    RT_3,
};
