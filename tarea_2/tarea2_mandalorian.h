#define ALTO 32  // 15
#define ANCHO 32 // 13

GLubyte paleta1[12][3] = {
    {255, 255, 255},
    {0, 0, 0},
    {154, 116, 97},
    {191, 191, 191},
    {250, 243, 163},
    {90, 67, 55},
    {64, 64, 64},
    {141, 129, 121},
    {162, 184, 133},
    {61, 85, 41},
    {141, 129, 121},
    {231, 222, 220}
};

GLubyte mandalorian[ALTO][ANCHO] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 11, 10, 11, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 10, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 10, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 11, 11, 11, 11, 11, 10, 11, 11, 11, 11, 11, 1, 0, 0, 0, 0, 1, 5, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 1, 0, 0, 0, 1, 5, 5, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 1, 0, 1, 5, 5, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 11, 10, 1, 1, 5, 5, 5, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 11, 11, 11, 11, 1, 11, 11, 11, 11, 10, 1, 1, 5, 5, 5, 5, 5, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 10, 11, 11, 11, 1, 11, 11, 10, 10, 10, 1, 5, 5, 5, 5, 5, 5, 5, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 10, 10, 10, 11, 1, 11, 10, 10, 10, 10, 1, 5, 5, 5, 5, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 10, 10, 10, 10, 11, 1, 11, 10, 10, 10, 10, 1, 5, 5, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 10, 10, 10, 11, 1, 11, 10, 10, 10, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 2, 2, 2, 2, 5, 2, 2, 2, 2, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 9, 1, 2, 2, 2, 2, 5, 2, 2, 2, 2, 1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 9, 1, 1, 4, 2, 2, 2, 2, 2, 4, 1, 1, 9, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 6, 1, 4, 4, 2, 2, 2, 4, 4, 1, 6, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 2, 2, 1, 6, 1, 5, 2, 5, 3, 5, 2, 5, 1, 6, 1, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 4, 6, 6, 1, 1, 8, 8, 4, 4, 4, 8, 8, 1, 1, 6, 6, 4, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 3, 3, 1, 4, 6, 4, 1, 1, 8, 8, 8, 8, 8, 8, 8, 1, 1, 4, 6, 4, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 3, 3, 1, 0, 1, 1, 1, 1, 2, 8, 1, 1, 1, 1, 1, 8, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 3, 3, 1, 1, 3, 1, 6, 1, 2, 8, 1, 6, 6, 6, 1, 8, 2, 1, 6, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 3, 3, 1, 3, 3, 3, 1, 1, 7, 7, 1, 6, 6, 6, 6, 6, 1, 7, 7, 1, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 3, 1, 3, 3, 3, 1, 6, 1, 2, 2, 1, 6, 6, 6, 6, 6, 1, 2, 2, 1, 6, 6, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 3, 3, 1, 1, 0, 1, 7, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 2, 7, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 2, 2, 7, 7, 1, 0, 0, 0, 0, 0, 1, 7, 7, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 1, 5, 5, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
