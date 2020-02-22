#include "include/ch16_blob_template.h"

#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    {
        BlobTemplate<int> ia;
        BlobTemplate<int> ia2 = {1, 2, 3, 4, 5};

        BlobTemplate<string> sa;
        BlobTemplate<string> sa2 = {"name", "gender"};

        BlobTemplate<int> iSquares = {0, 1, 2, 3, 4, 5};
        for (int i = 0; i < iSquares.size(); ++i) {
            iSquares[i] *= 2;
        }
    }

    {
        using ShaStrBlob = BlobTemplate<string>;
        ShaStrBlob sa3 = {"hi", "how", "are", "you"};
        for (int i = 0; i < sa3.size(); ++i) {
            cout << sa3[i] << " ";
        }
        cout << endl;
    }

    {
        // 实例化，成员模板
        int ia[] = {1, 2, 3, 4, 5, 6};
        vector<long> vi = {0, 1, 2, 3, 4, 5, 6, 7};
        list<const char*> w = {"now", "is", "the", "time"};

        // 实例化BlobTemplate<int>类，及其接受两个int*参数的构造函数
        BlobTemplate<int> blob_ia(begin(ia), end(ia));
        // 实例化BlobTemplate<int>类，及其接受两个vector<int>::iterator参数的构造函数
        BlobTemplate<int> blob_ia2(vi.begin(), vi.end());
        // 实例化BlobTemplateb<string>类，及其接受两个vector<string>::iterator参数的构造函数
        BlobTemplate<string> blob_sa(w.begin(), w.end());
    }

    return 0;
}