void multiply(float* result, float* a, float* b) {
    float a00 = a[0 * 3 + 0];
    float a01 = a[0 * 3 + 1];
    float a02 = a[0 * 3 + 2];
    float a10 = a[1 * 3 + 0];
    float a11 = a[1 * 3 + 1];
    float a12 = a[1 * 3 + 2];
    float a20 = a[2 * 3 + 0];
    float a21 = a[2 * 3 + 1];
    float a22 = a[2 * 3 + 2];
    float b00 = b[0 * 3 + 0];
    float b01 = b[0 * 3 + 1];
    float b02 = b[0 * 3 + 2];
    float b10 = b[1 * 3 + 0];
    float b11 = b[1 * 3 + 1];
    float b12 = b[1 * 3 + 2];
    float b20 = b[2 * 3 + 0];
    float b21 = b[2 * 3 + 1];
    float b22 = b[2 * 3 + 2];
 
    float newResult[] = {
      b00 * a00 + b01 * a10 + b02 * a20,
      b00 * a01 + b01 * a11 + b02 * a21,
      b00 * a02 + b01 * a12 + b02 * a22,
      b10 * a00 + b11 * a10 + b12 * a20,
      b10 * a01 + b11 * a11 + b12 * a21,
      b10 * a02 + b11 * a12 + b12 * a22,
      b20 * a00 + b21 * a10 + b22 * a20,
      b20 * a01 + b21 * a11 + b22 * a21,
      b20 * a02 + b21 * a12 + b22 * a22,
    };

    memcpy(result, newResult, sizeof(float) * 9);
}

void identity(float* result) {
    float newResult[] = {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 9);
}

void rotation(
    float* result,
    float rads
) {
    float c = cos(rads);
    float s = sin(rads);
    float newResult[] = {
        c, -s, 0,
        s, c, 0,
        0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 9);
}

// Converts from clip space (-1 to 1) to pixel space
void projection(
        float* result,
        float width,
        float height 
) {
    float newResult[] = {
        2 / width, 0, 0,
        0, -2 / height, 0,
        -1, 1, 1
    };

    memcpy(result, newResult, sizeof(float) * 9);
}

void translation(
        float* result,
        float x,
        float y
) {
    float newResult[] = {
        1, 0, 0,
        0, 1, 0,
        x, y, 1
    };

    memcpy(result, newResult, sizeof(float) * 9);
}

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

