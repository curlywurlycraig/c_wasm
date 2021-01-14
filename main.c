// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setModelViewMatrix(float* matrix);
float random();
float sin(float rads);
float cos(float rads);

#include "mem.c"
#include "math.c"

const float CANVAS_WIDTH = 800.0f;
const float CANVAS_HEIGHT = 600.0f;

float* vertices = 0;
static unsigned int MAX_VERTICES = 1000;

// 8000 is 4 (float size) * 2 (two floats per vertex) * 1000 (number of vertices)
float* modelViewMatrix = (float*) 8000;

float xOffset = 100;
float yOffset = 100;

float time = 0;

void init() {
    identity(modelViewMatrix);

    float projectionMatrix[9];
    float translationMatrix[9];
    float originTranslationMatrix[9];
    float rotationMatrix[9];

    xOffset = 200 + sin(time) * 100;
    translation(translationMatrix, xOffset, yOffset);
    translation(originTranslationMatrix, -50, -50);
    projection(projectionMatrix, CANVAS_WIDTH, CANVAS_HEIGHT);
    rotation(rotationMatrix, time);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            projectionMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            translationMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            rotationMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            originTranslationMatrix);

    setModelViewMatrix(modelViewMatrix);

    time += 0.01;
}

void iter() {
    init();

    const float newVertices[] = {
        10.0f, 10.0f,
        100.0f, 10.0f,
        100.0f, 100.0f,
        10.0f, 100.0f,
    };

    memcpy(vertices, newVertices, sizeof(float) * 8);
    drawVertexBuffer(vertices, 4);
}
