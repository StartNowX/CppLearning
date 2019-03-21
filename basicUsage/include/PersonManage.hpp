#include <cstring>

class PersonManage{
private:
    char *name;
    int age;
    int height;

    //const int MONTHS = 12;
    enum {MONTHS = 12};
    double salary[12];

public:
    PersonManage();
    PersonManage(const std::string& name, const int age, const int height);
    ~PersonManage();

    void SetName(const std::string& s);
    void SetName(const std::string& s) const;

    void GetName() const;
};
