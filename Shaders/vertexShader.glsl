// Declaração dos atributos de entrada
attribute vec3 position;
attribute vec3 normal;

// Declaração das variáveis de saída
varying vec3 fragPosition;
varying vec3 fragNormal;

void main() {
    // Passa os valores dos atributos para as variáveis de saída
    fragPosition = position;
    fragNormal = normal;

    // Define a posição final do vértice
    gl_Position = vec4(position, 1.0);
}
