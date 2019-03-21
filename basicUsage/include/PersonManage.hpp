#include <cstring>

class PersonManage{
private:
    char *name;
    int age;
    int height;

public:
    PersonManage();
    PersonManage(const std::string& name, const int age, const int height);
    ~PersonManage();

    void SetName(const std::string& s);
    void SetName(const std::string& s) const;

    void GetName() const;
};
