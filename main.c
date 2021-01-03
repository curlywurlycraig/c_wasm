// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);

int col = 0;

int add(int a, int b) {
    return a + b;
}

void iter() {
    float fcol = (float) col / 255.0f;
    glClear(fcol, 0.0, 0.0, 1.0);
    col++;
    col = col % 255;
}
