// JS imports
void prints(const char *address);
void printfl(float num);
void glClear(float r, float g, float b, float a);

int col = 0;
int other = 10;

int add(int a, int b) {
    return a + b;
}

typedef struct vec3 vec3;
struct vec3 {
    unsigned char a;
    unsigned char b;
    unsigned char c;
    unsigned int d;
};

void iter() {
    int *p = 0;
    *p = col;

    float fcol = (float) col / 255.0f;
    glClear(fcol, 0.0, 1.0 - fcol, 1.0);
    col++;
    col = col % 255;
}
