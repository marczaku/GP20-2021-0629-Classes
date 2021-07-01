#include <iostream>

using namespace std;

class Foo{
public:
    char arr[10];
    Foo(){
        const char* hello = "Hello";
        memcpy(arr, hello, sizeof(hello));
    }
    char& operator[](int index){
        return arr[index];
    }
};

int main(int argc, char *argv[])
{
    Foo foo;
    foo[0] = 'B';
    cout << foo.arr; // print: Bello
}
