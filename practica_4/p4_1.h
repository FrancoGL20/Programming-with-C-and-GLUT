float Coordenadas[4][3] = {{0, 0, 1}, {100, 0, 1}, {150, 50, 1}, {50, 50, 1}};
float Translacion[3][3]= {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
float Escalamiento[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
float Rotacion[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

// Función para crear la matriz de translación homogénea
void creaT(int dx, int dy) {
    float Translacion2[3][3] = {{1, 0, dx}, {0, 1, dy}, {0, 0, 1}};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Translacion[i][j] = Translacion2[i][j];
}

// Función para crear la matriz de escalamiento homogénea
void matriz_escalamiento(float s_x, float s_y) {
    float Escalamiento2[3][3] = {{s_x, 0, 0}, {0, s_y, 0}, {0, 0, 1}};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Escalamiento[i][j] = Escalamiento2[i][j];
}

// Función para crear la matriz de rotación homogénea
void matriz_rotacion(float angulo) {
    float Rotacion[3][3] = {{cos(angulo), -sin(angulo), 0}, {sin(angulo), cos(angulo), 0}, {0, 0, 1}};
}

// Función para crear la matriz de reflexión homogénea
void matrices_suma(int r, int c, float matrizA[][c], float matrizB[][c], float matrizC[][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            matrizC[i][j] = matrizA[i][j] + matrizB[i][j];
        }
    }
}

// Función para hacer la multiplicación de matrices
void matrices_multiplicacion(int m, int n, int q, float matrizA[][q], float matrizB[][m], float matrizC[][m]) {
    for (int a = 0; a < m; a++) {
        // Dentro recorremos las filas de la primera (A)
        for (int i = 0; i < n; i++) {
            float suma = 0;
            // Y cada columna de la primera (A)
            for (int j = 0; j < q; j++) {
                // Multiplicamos y sumamos resultado
                suma += matrizA[i][j] * matrizB[j][a];
            }
            // Lo acomodamos dentro del producto
            matrizC[i][a] = suma;
        }
    }
}

// Función para multiplicar una matriz por un vector
void matrices_multiplicacion_vector() {
    for (int i = 0; i < 4; i++) {
        float array[3][1];
        float x = Coordenadas[i][0];
        float y = Coordenadas[i][1];
        array[0][0] = x;
        array[1][0] = y;
        array[2][0] = 1;
        matrices_multiplicacion(1, 3, 3, Translacion, array, array);
        Coordenadas[i][0] = array[0][0];
        Coordenadas[i][1] = array[1][0];
    }
}

// Función para crear la matriz de escalamiento homogénea
void creaS(int d, float vector[d], float matriz[][d]) {
    for (int i = 0; i < d; i++) {
        matriz[i][i] = vector[i];
    }
}
