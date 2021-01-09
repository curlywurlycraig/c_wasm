// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setTranslation(float x, float y);

// TODO
void perspective(
        float** result,
        float fieldOfView,
        float aspect,
        float zNear,
        float zFar
) {
    
}

int col = 0;

int add(int a, int b) {
    return a + b;
}

typedef struct vec3 vec3;
struct vec3 {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned int d;
};

void iter() {
    float *p = 0;
    *p = col;

    float fcol = (float) col / 255.0f;
    setTranslation(fcol, fcol);

    float* vertices = sizeof(p);
    *(vertices) = -0.5f;
    *(vertices+1) = -0.5f;
    *(vertices+2) = 0.5f;
    *(vertices+3) = -0.5f;
    *(vertices+4) = 0.5f;
    *(vertices+5) = 0.5f;
    *(vertices+6) = -0.5f;
    *(vertices+7) = 0.5f;
    drawVertexBuffer(vertices, 4);

    col += 10;
    col = col % 255;
}
