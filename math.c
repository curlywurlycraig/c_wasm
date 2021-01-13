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

