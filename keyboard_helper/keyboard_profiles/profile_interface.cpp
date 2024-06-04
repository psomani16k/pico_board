#include <string>
#include "keyboard_helper/layout/keyboard_layout.cpp"
#include "enum_declarations.cpp"
#include <vector>

enum KeyCodes;

class ProfileInterface{
public:
    virtual std::string getName() = 0;
    virtual std::vector<int *> getReport(LayoutReadReport readReport) const = 0;
    virtual std::vector<int *> getBootReport(LayoutReadReport readReport) const = 0;
};

class KeyProcessor{
public:
    virtual std::vector<std::vector<KeyCodes>> getReport() = 0;
};

class SingleKeyProcessor : public KeyProcessor{
private:
    KeyCodes key;
public:

    SingleKeyProcessor(KeyCodes keyCode)
    {
        key = keyCode;
    }

    std::vector<std::vector<KeyCodes>> getReport()
    {
        std::vector<std::vector<KeyCodes>> result = {{key}};
        return result;
    }
};
