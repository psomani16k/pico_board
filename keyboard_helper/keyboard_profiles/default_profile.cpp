#include "keyboard_helper/keyboard_profiles/profile_interface.cpp"
#include "keyboard_helper/layout/keyboard_layout.cpp"
#include <map>

class DefaultProfile : public ProfileInterface
{
private:

    // std::map<KeyLocation, std::vector<> > mapper = 
    // {
        // {C1_2, {
                //    KEY_CAPS_LOCK,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C1_3, {
                //    KEY_ESCAPE,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C2_1, {
                //    KEY_Z,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C2_2, {
                //    KEY_A,
                //    KEY_1,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C2_3, {
                //    KEY_Q,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C3_1, {
                //    KEY_X,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C3_2, {
                //    KEY_S,
                //    KEY_2,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C3_3, {
                //    KEY_W,
                //    KEY_GRAVE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C4_1, {
                //    KEY_C,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C4_2, {
                //    KEY_D,
                //    KEY_3,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C4_3, {
                //    KEY_E,
                //    KEY_BRACKET_LEFT,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C5_1, {
                //    KEY_V,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C5_2, {
                //    KEY_F,
                //    KEY_4,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C5_3, {
                //    KEY_R,
                //    KEY_BRACKET_RIGHT,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C6_1, {
                //    KEY_B,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C6_2, {
                //    KEY_G,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C6_3, {
                //    KEY_T,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C7_1, {
                //    KEY_N,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C7_2, {
                //    KEY_H,
                //    KEY_6,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C7_3, {
                //    KEY_Y,
                //    KEY_MINUS,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C8_1, {
                //    KEY_M,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C8_2, {
                //    KEY_J,
                //    KEY_7,
                //    KEY_ARROW_LEFT,
                //    KEY_NONE,
            //    }},
        // {C8_3, {
                //    KEY_U,
                //    KEY_EQUAL,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C9_1, {
                //    KEY_COMMA,
                //    KEY_NONE,
                //    KEY_NONE,
                //    KEY_NONE,
            //    }},
        // {C9_2, {
                //    KEY_K,
                //    KEY_8,
                //    KEY_ARROW_DOWN,
                //    KEY_NONE,
            //    }},
        // {C9_3, {
                //    KEY_I,
                //    KEY_APOSTROPHE,
                //    KEY_ARROW_UP,
                //    KEY_NONE,
            //    }},
        // {C10_1, {
                    // KEY_PERIOD,
                    // KEY_NONE,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C10_2, {
                    // KEY_L,
                    // KEY_9,
                    // KEY_ARROW_RIGHT,
                    // KEY_NONE,
                // }},
        // {C10_3, {
                    // KEY_O,
                    // KEY_DELETE,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C11_1, {
                    // KEY_SLASH,
                    // KEY_NONE,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C11_2, {
                    // KEY_SEMICOLON,
                    // KEY_0,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C11_3, {
                    // KEY_P,
                    // KEY_BACKSLASH,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C12_2, {
                    // KEY_ENTER,
                    // KEY_BRACKET_LEFT,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},
        // {C12_3, {
                    // KEY_BACKSPACE,
                    // KEY_BRACKET_LEFT,
                    // KEY_NONE,
                    // KEY_NONE,
                // }},

    // };

    std::vector<int *> defaultProcessor(LayoutReadReport readReport) const
    {
        std::vector<KeyLocation> keypressed = readReport.getPressedKeys();
        for (uint8_t i = 0; i < keypressed.size(); i++)
        {
            mapper[keypressed[i]].
        }
        
    }
    std::vector<int *> fnOneProcessor(LayoutReadReport readReport) const {}
    std::vector<int *> fnTwoProcessor(LayoutReadReport readReport) const {}
    std::vector<int *> fnOneAndTwoProcessor(LayoutReadReport readReport) const
    {
    }

public:
    std::vector<int *> getReport(LayoutReadReport readReport) const override
    {
        bool fn1 = readReport.getKey(KeyLocation::RT_3);
        bool fn2 = readReport.getKey(KeyLocation::LT_3);

        if (fn1 && fn2)
        {
            return fnOneAndTwoProcessor(readReport);
        }
        else if (fn1)
        {
            return fnOneProcessor(readReport);
        }
        else if (fn2)
        {
            return fnTwoProcessor(readReport);
        }
        return defaultProcessor(readReport);
    }
};

//                col 1    col 2    col 3    col 4    col 5    col 6        col 7    col 8    col 9   col 10   col 11   col 12
//
//             +========+========+========+========+========+========++ ++========+========+========+========+========+========+
//  row 3   =  |  C1_3  |  C2_3  |  C3_3  |  C4_3  |  C5_3  |  C6_3  || ||  C7_3  |  C8_3  |  C9_3  | C10_3  | C11_3  | C12_3  |
//             |~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|| ||~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|
//             |   esc  |    q   |    w   |    e   |    r   |    t   || ||    y   |    u   |    i   |    o   |    p   | bckspc |
//             |        |        |    `   |    [   |    ]   |        || ||    -   |    =   |    '   |  del   |    \   |        |
//             |        |        |        |        |        |        || ||        |        | up_arw |        |        |        |
//             |        |        |        |        |        |        || ||        |        |        |        |        |        |
//             +--------+--------+--------+--------+--------+--------++ ++--------+--------+--------+--------+--------+--------+
//  row 2   =  |  C1_2  |  C2_2  |  C2_2  |  C4_2  |  C5_2  |  C6_2  || ||  C7_2  |  C8_2  |  C9_2  | C10_2  | C11_2  | C12_2  |
//             |~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|| ||~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|
//             | cpslck |    a   |    s   |    d   |    f   |    g   || ||    h   |    j   |    k   |    l   |    ;   |  entr  |
//             |        |    1   |    2   |    3   |    4   |    5   || ||    6   |    7   |    8   |    9   |    0   |        |
//             |        |        |        |        |        |        || ||        | lt_arw | dw_arw | rt_arw |        |        |
//             |        |        |        |        |        |        || ||        |        |        |        |        |        |
//             +--------+--------+--------+--------+--------+--------++ ++--------+--------+--------+--------+--------+--------+
//  row 1   =  |  C1_1  |  C2_1  |  C3_1  |  C4_1  |  C5_1  |  C6_1  || ||  C7_1  |  C8_1  |  C9_1  | C10_1  | C11_1  | C12_1  |
//             |~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|| ||~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|~~~~~~~~|
//             | l_shft |    z   |    x   |    c   |    v   |    b   || ||    n   |    m   |    ,   |    .   |    /   | r_shft |
//             |        |        |        |        |        |        || ||        |        |        |        |        |        |
//             |        |        |        |        |        |        || ||        |        |        |        |        |        |
//             |        |        |        |        |        |        || ||        |        |        |        |        |        |
//             +========+========+========+========+========+========++ ++========+========+========+========+========+========+
//
//                               +========+========+========+                     +========+========+========+
//                               |  LT_1  |  LT_2  |  LT_3  |                     |  RT_1  |  RT_2  |  RT_3  |
//                               |~~~~~~~~|~~~~~~~~|~~~~~~~~|                     |~~~~~~~~|~~~~~~~~|~~~~~~~~|
//                               |  win   |  alt   |  fn2   |                     |  spc   |  ctrl  |   fn1  |
//                               |        |        |        |                     |  tb    |        |        |
//                               |        |        |        |                     |        |        |        |
//                               |        |        |        |                     |        |        |        |
//                               +========+========+========+                     +========+========+========+


