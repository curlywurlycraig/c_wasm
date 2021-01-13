#include "mem.c"
#include "math.c"

// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setModelViewMatrix(float* matrix);
void setTranslation(float x, float y);
float random();

float* vertices = 0;
static unsigned int MAX_VERTICES = 1000;

void iter() {
    const float newVertices[] = {
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * -1.0f, random() * 1.0f,
    };

    memcpy(vertices, newVertices, sizeof(float) * 10);

    drawVertexBuffer(vertices, 5);
}
