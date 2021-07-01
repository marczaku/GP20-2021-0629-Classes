#include <string>

using namespace std;

namespace class_library {
    class Vector3 {
        public:
        float x,y,z;
        Vector3(float x, float y, float z) : x(x), y(y), z(z){}
        Vector3 operator+ (const Vector3& addend){ return Vector3(x+addend.x, y+addend.y, z+addend.z); }
        Vector3 operator- (const Vector3& subtrahend){ return Vector3(x-subtrahend.x, y-subtrahend.y, z-subtrahend.z); }
        float operator*(const Vector3& other){return x*other.x + y*other.y + z*other.z;}
        Vector3 operator^ (const Vector3& other){ return Vector3(
            y*other.z - z*other.y,
            z*other.x - x*other.z,
            x*other.y - y*other.x);
        }
    };
}