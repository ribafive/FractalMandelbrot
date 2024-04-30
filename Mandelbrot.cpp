#include <iostream>
#include <fstream>

class Mandelbrot {
private:
    static const int MAX_ITERATION = 1000;

    struct Complex {
        double real, imag; // Partes real e imaginária do número complexo
        Complex (double r, double i) : real(r), imag(i) {} // Construtor da estrutura
        double magnitude () { // Método para calcular o módulo do número complexo
            return real * real + imag * imag;
        }
    Complex operator*(const Complex& other) {
        return Complex( real * other.real - imag * other.imag,
                        real * other.imag + imag * other.real);
    }
    Complex operator+(const Complex& other){
        return Complex( real + other.real, imag + other.imag);
    }
};
public:
    static int calculateIterations(double real, double imag){
        Complex c(real, imag);
        Complex z(0,0);
        int iterations = 0;
        while (z.magnitude() <= 4 && iterations < MAX_ITERATION) { //Loop para caluclar as iterações
            z = z * z + c; //Atualização de z de acordo com a fórmula do conjunto de Mandelbrot
            iterations++; //Incremento do contador de iterações
        }
        return iterations; //Retorno do número de iterações
    }

};

int main() {
    std::ofstream image ("mandelbrot.ppm"); //Abertura do arquivo para escrita da imagem
    image <<"P3\n1600 1200\n255\n"; //Cabeçalho do arquivo PPM indicando largura, altura e valor máximo de cor

    for (int y = 0; y < 1200; ++y){//Loop para percorrer as linhas da imagem
        for (int x = 0; x < 1600; ++x) { // Loop para percorrer as colunas da imagem
        double real = (x - 1600 / 2.0) * 4.0 / 1600; // Cálculo da parte real do número complexo associado ao pixel
            double imag = (y - 1200 / 2.0) * 4.0 / 1600; // Cálculo da parte imaginária do número complexo associado ao pixel
            int iterations = Mandelbrot::calculateIterations(real, imag); // Chamada do método estático para calcular o número de iterações
            int r = (iterations * 17) % 256; // Cálculo do valor da componente vermelha
            int g = (iterations * 31) % 256; // Cálculo do valor da componente verde
            int b = (iterations * 47) % 256; // Cálculo do valor da componente azul
            image << r << " " << g << " " << b << "\n";// Escrita das componentes RGB no arquivo PPM
    }
}

image.close(); // Fechamento do arquivo de imagem
std::cout <<"Image generated successfully!\n"; // Mensagem indicando que a imagem foi gerada com sucesso
return 0;
}
