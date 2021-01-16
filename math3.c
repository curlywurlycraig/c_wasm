static float PI = 3.14159f;

// A lot of this code came from the guidance at
// https://webglfundamentals.org/webgl/lessons/webgl-3d-orthographic.html

void multiply(float* result, float* a, float* b) {
    float b00 = b[0 * 4 + 0];
    float b01 = b[0 * 4 + 1];
    float b02 = b[0 * 4 + 2];
    float b03 = b[0 * 4 + 3];
    float b10 = b[1 * 4 + 0];
    float b11 = b[1 * 4 + 1];
    float b12 = b[1 * 4 + 2];
    float b13 = b[1 * 4 + 3];
    float b20 = b[2 * 4 + 0];
    float b21 = b[2 * 4 + 1];
    float b22 = b[2 * 4 + 2];
    float b23 = b[2 * 4 + 3];
    float b30 = b[3 * 4 + 0];
    float b31 = b[3 * 4 + 1];
    float b32 = b[3 * 4 + 2];
    float b33 = b[3 * 4 + 3];
    float a00 = a[0 * 4 + 0];
    float a01 = a[0 * 4 + 1];
    float a02 = a[0 * 4 + 2];
    float a03 = a[0 * 4 + 3];
    float a10 = a[1 * 4 + 0];
    float a11 = a[1 * 4 + 1];
    float a12 = a[1 * 4 + 2];
    float a13 = a[1 * 4 + 3];
    float a20 = a[2 * 4 + 0];
    float a21 = a[2 * 4 + 1];
    float a22 = a[2 * 4 + 2];
    float a23 = a[2 * 4 + 3];
    float a30 = a[3 * 4 + 0];
    float a31 = a[3 * 4 + 1];
    float a32 = a[3 * 4 + 2];
    float a33 = a[3 * 4 + 3];
    
    float newResult[] = {
      b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30,
      b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31,
      b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32,
      b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33,
      b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30,
      b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31,
      b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32,
      b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33,
      b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30,
      b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31,
      b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32,
      b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33,
      b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30,
      b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31,
      b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32,
      b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33,
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void identity(float* result) {
    float newResult[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void scale(
    float* result,
    float sx,
    float sy,
    float sz
) {
    float newResult[] = {
        sx, 0, 0, 0,
        0, sy, 0, 0,
        0, 0, sz, 0,
        0, 0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void rotationx(
    float* result,
    float rads
) {
    float c = cos(rads);
    float s = sin(rads);
    float newResult[] = {
        1, 0, 0, 0,
        0, c, s, 0,
        0, -s, c, 0,
        0, 0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void rotationy(
    float* result,
    float rads
) {
    float c = cos(rads);
    float s = sin(rads);
    float newResult[] = {
        c, 0, -s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void rotationz(
    float* result,
    float rads
) {
    float c = cos(rads);
    float s = sin(rads);
    float newResult[] = {
        c, s, 0, 0,
        -s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

// https://webglfundamentals.org/webgl/lessons/webgl-3d-perspective.html
void perspective(
        float* result,
        float fovRad,
        float aspect,
        float near,
        float far
) {
    float f = tan(PI * 0.5f - 0.5f * fovRad);
    float rangeInv = 1.0f / (near - far);
    float newResult[] = {
        f / aspect, 0, 0, 0,
        0, f, 0, 0,
        0, 0, (near + far) * rangeInv, -1,
        0, 0, near * far * rangeInv * 2, 0
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

void translation(
        float* result,
        float x,
        float y,
        float z
) {
    float newResult[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        x, y, z, 1
    };

    memcpy(result, newResult, sizeof(float) * 16);
}

