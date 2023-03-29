void suma (int r, int c, float ma[][c], float mb[][c], float mc[][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            mc[i][j] = ma[i][j] + mb[i][j];
        }
    }
}

// Fuente: https://www.scaler.com/topics/matrix-multiplication-in-c/
void multiplicacion (int r, int c, float ma[][c], float mb[][c], float mc[][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            for (int k = 0; k < r; k++) {
                mc[i][j] += ma[i][k] * mb[k][j];
            }
        }
    }    
}

void creaS(int d, float v[d], float m[][d]) {
    for (int i = 0; i < d; i++) {
        m[i][i] = v[i];
    }
}

void imprime(int r, int c, float m[][c]) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%.2f\t", m[i][j]);
        }
        printf("\n");
    }
}