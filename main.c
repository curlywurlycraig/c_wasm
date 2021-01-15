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
#include "math3.c"

const float CANVAS_WIDTH = 800.0f;
const float CANVAS_HEIGHT = 600.0f;

float* lines = 0;
static unsigned int MAX_VERTICES = 1000;

// 8000 is 4 (float size) * 3 (three floats per vertex) * 1000 (number of vertices)
float* modelViewMatrix = (float*) 12000;

float xOffset = 400;
float yOffset = 200;
float zOffset = 0;

float time = 0;

void init() {
    identity(modelViewMatrix);

    float projectionMatrix[16];
    float translationMatrix[16];
    float originTranslationMatrix[16];
    float rotationYMatrix[16];
    float rotationXMatrix[16];
    float rotationZMatrix[16];
    float scaleMatrix[16];

    // xOffset = 200 + sin(time) * 100;
    // float theScale = sin(time) * 0.01;
    float theScale = 1;

    translation(translationMatrix, xOffset + sin(time) * 100, yOffset, zOffset);
    translation(originTranslationMatrix, -55, -55, -50);
    projection(projectionMatrix, CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_WIDTH);
    rotationz(rotationZMatrix, time * 0.8);
    rotationx(rotationXMatrix, -time);
    rotationy(rotationYMatrix, time * -0.5);
    scale(scaleMatrix, theScale, theScale, theScale);

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
            rotationYMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            rotationXMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            rotationZMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            originTranslationMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            scaleMatrix);

    setModelViewMatrix(modelViewMatrix);

    time += 0.02;
}

void iter() {
    init();

    // a cube
    const float newLines[] = {
        // front face
        10.0f, 10.0f, 10.0f,
        100.0f, 10.0f, 10.0f,

        100.0f, 10.0f, 10.0f,
        100.0f, 100.0f, 10.0f,

        100.0f, 100.0f, 10.0f,
        10.0f, 100.0f, 10.0f,

        10.0f, 100.0f, 10.0f,
        10.0f, 10.0f, 10.0f,

        // back face
        10.0f, 10.0f, 100.0f,
        100.0f, 10.0f, 100.0f,

        100.0f, 10.0f, 100.0f,
        100.0f, 100.0f, 100.0f,

        100.0f, 100.0f, 100.0f,
        10.0f, 100.0f, 100.0f,

        10.0f, 100.0f, 100.0f,
        10.0f, 10.0f, 100.0f,

        // connections between front and back
        10.0f, 10.0f, 10.0f,
        10.0f, 10.0f, 100.0f,

        100.0f, 10.0f, 10.0f,
        100.0f, 10.0f, 100.0f,

        10.0f, 100.0f, 10.0f,
        10.0f, 100.0f, 100.0f,

        100.0f, 100.0f, 10.0f,
        100.0f, 100.0f, 100.0f,
    };

    memcpy(lines, newLines, sizeof(float) * 72);
    drawVertexBuffer(lines, 24);
}
