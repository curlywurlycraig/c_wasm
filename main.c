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
    float fcol = (float) col / 255.0f;
    setTranslation(fcol, fcol);

    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    drawVertexBuffer(vertices, 4);

    col += 2;
    col = col % 255;
}
