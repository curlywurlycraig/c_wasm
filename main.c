// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);
void drawVertexBuffer(float* vertices, unsigned int vertexCount);
void setTranslation(float x, float y);
float random();

// Create a perspective matrix
// TODO
void perspective(
        float** result,
        float fieldOfView,
        float aspect,
        float zNear,
        float zFar
) {
    
}

// Why? The compiler occasionally will optimize large inline arrays
// by placing them in .data (?), then memcpy-ing them out, or something.
// There doesn't appear to be any way around this:
//     https://www.raspberrypi.org/forums/viewtopic.php?t=219687
char* memcpy(char* dest, const char* src, unsigned int n) {
    for (int i = 0; i < n; i++) {
        *(dest+i) = *(src+i);
    }

    return dest;
}

void iter() {
    const float vertices[] = {
        -1 + 2 * random(), -1 + 2 * random(), -1 + 2 * random(),
        -1 + 2 * random(), -1 + 2 * random(), -1 + 2 * random(),
        -1 + 2 * random(), -1 + 2 * random(), -1 + 2 * random(),
        -1 + 2 * random(), -1 + 2 * random(), -1 + 2 * random(),
    };

    drawVertexBuffer((float*) vertices, 4);
}
