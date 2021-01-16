// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setModelViewMatrix(float* matrix);
float random();
float sin(float rads);
float cos(float rads);
float tan(float rads);

#include "mem.c"
#include "math3.c"

const float CANVAS_WIDTH = 800.0f;
const float CANVAS_HEIGHT = 600.0f;

float* lines = 0;
static unsigned int MAX_VERTICES = 1000;

// 8000 is 4 (float size) * 3 (three floats per vertex) * 1000 (number of vertices)
float* modelViewMatrix = (float*) 12000;

float xOffset = 0;
float yOffset = 0;
float zOffset = -200;

float time = 0;

float cursorX = 400.0f;
float cursorY = 300.0f;
void setCursorPosition(float x, float y) {
    cursorX = x;
    cursorY = y;
}

void init() {
    identity(modelViewMatrix);

    float perspectiveMatrix[16];
    float translationMatrix[16];
    float originTranslationMatrix[16];
    float rotationYMatrix[16];
    float rotationXMatrix[16];
    float rotationZMatrix[16];
    float scaleMatrix[16];

    //float theScale = sin(time) * 0.01;
    float theScale = 1;

    float fovRad = (87.0f / 360.0f) * PI * 2;
    float aspect = CANVAS_WIDTH / CANVAS_HEIGHT;
    float near = 1;
    float far = 2000;

    translation(translationMatrix, xOffset, yOffset, zOffset);
    translation(originTranslationMatrix, -55, -55, -55);
    perspective(perspectiveMatrix, fovRad, aspect, near, far);
    rotationz(rotationZMatrix, 0);
    rotationx(rotationXMatrix, cursorY * 0.01f);
    rotationy(rotationYMatrix, cursorX * 0.01f);
    scale(scaleMatrix, theScale, theScale, theScale);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            perspectiveMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            translationMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            rotationXMatrix);

    multiply(
            modelViewMatrix,
            modelViewMatrix,
            rotationYMatrix);

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
