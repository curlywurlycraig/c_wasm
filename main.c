#include "mem.c"
#include "math.c"

// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setModelViewMatrix(float* matrix);
float random();

float* vertices = 0;
static unsigned int MAX_VERTICES = 1000;

static unsigned int FLOAT_SIZE = 4; // 4 byte floats

float* translationMatrix = (float*) 8000;

float xOffset = 0;
float yOffset = 0;

void iter() {
    const float newVertices[] = {
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * 1.0f, random() * 1.0f,
        random() * -1.0f, random() * 1.0f,
    };

    memcpy(vertices, newVertices, sizeof(float) * 10);

    translation(translationMatrix, xOffset, yOffset);
    setModelViewMatrix(translationMatrix);

    drawVertexBuffer(vertices, 5);

    yOffset += 0.1;
    xOffset += 0.1;
}
