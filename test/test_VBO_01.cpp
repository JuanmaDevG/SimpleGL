#include "VBO.hpp"

using namespace std;

/*
    VBO information print
*/
int main()
{
    glewExperimental = true;
    glewInit();

    const float data[] = {
        //Position          Color
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    const uint8_t f_per_vert[] = {
        3, 3
    };

    VertexBuffer VBO(data, sizeof(data)/sizeof(float), f_per_vert, sizeof(f_per_vert)/sizeof(uint8_t));

    cout << "VBO = " << VBO << endl;
}