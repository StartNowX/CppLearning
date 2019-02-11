#include <iostream>
#include <string>

class FABU{
public:
    FABU();
    ~FABU();

    int addMem(int memId, std::string& name);
    int showNum();

private:
    std::string memName;
    int memID;
    int totalNum;
};
