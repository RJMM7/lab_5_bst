#include <iostream>
using namespace std;

struct Estudiante
{
    int carnet;
    char nombre[50];
    float nota;
    Estudiante *izquierdo;
    Estudiante *derecho;
};

// Función para crear un nuevo estudiante
Estudiante *crearEstudiante(int carnet, char nom[], float nota)
{
    Estudiante *nuevo = new Estudiante();
    nuevo->carnet = carnet;
    nuevo->nota = nota;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;

    // Copiar el nombre
    int i = 0;
    while (nom[i] != '\0' && i < 49)
    {
        nuevo->nombre[i] = nom[i];
        i++;
    }
    nuevo->nombre[i] = '\0';

    return nuevo;
}

// TODO: Implementar estas funciones

// 1. Insertar un estudiante en el árbol (ordenado por carnet)
Estudiante *insertar(Estudiante *raiz, int carnet, char nombre[], float nota)
{
    // Si la lista esta vacia, se agrega un nuevo estudiante
    if (raiz == NULL)
    {
        return crearEstudiante(carnet, nombre, nota);
    }

    // Cosas para ver si se va al lado izquierdo o derecho
    if (carnet < raiz->carnet)
    {
        raiz->izquierdo = insertar(raiz->izquierdo, carnet, nombre, nota);
    }
    else if (carnet > raiz->carnet)
    {
        raiz->derecho = insertar(raiz->derecho, carnet, nombre, nota);
    }
    else
    {
        cout << "El carnet ya existe" << endl;
    }

    return raiz;
}

// 2. Mostrar todos los estudiantes en orden de carnet
void mostrarEstudiantes(Estudiante *raiz)
{
    // Verifica si la raiz es dintinto del vacio
    if (raiz != NULL)
    {
        mostrarEstudiantes(raiz->izquierdo);
        cout << "Carnet: " << raiz->carnet
             << ", Nombre: " << raiz->nombre
             << ", Nota: " << raiz->nota << endl;
        mostrarEstudiantes(raiz->derecho);
    }
}

// 3. Buscar un estudiante por carnet y mostrar sus datos
void buscarEstudiante(Estudiante *raiz, int carnet)
{
    // Verifica si la raiz es vacia
    if (raiz == NULL)
    {
        cout << "Estudiante no encontrado" << endl;
        return;
    }

    // Verifica si el carnet coincide
    if (carnet == raiz->carnet)
    {
        cout << "Carnet: " << raiz->carnet
             << ", Nombre: " << raiz->nombre
             << ", Nota: " << raiz->nota << endl;
    }
    else if (carnet < raiz->carnet)
    {
        buscarEstudiante(raiz->izquierdo, carnet);
    }
    else
    {
        buscarEstudiante(raiz->derecho, carnet);
    }
}

// 4. Mostrar estudiantes aprobados (nota >= 6.0)
void mostrarAprobados(Estudiante *raiz)
{
    // Verifica si la raiz es distinta del vacio
    if(raiz != NULL)
    {
        mostrarAprobados(raiz->izquierdo);

        if(raiz->nota >= 6)
        {
            cout << "Carnet: " << raiz->carnet
                 << ", Nombre: " << raiz->nombre
                 << ", Nota: " << raiz->nota << endl;
        }
        mostrarAprobados(raiz->derecho);
    }
}

// 5. Mostrar estudiantes reprobados (nota < 6.0)
void mostrarReprobados(Estudiante *raiz)
{
    if(raiz != NULL){
        mostrarReprobados(raiz->izquierdo);

        if(raiz->nota <6 ){
            cout << "Carnet: " << raiz->carnet 
            << ", nombre: " << raiz->nombre
            << ", nota: " << raiz->nota << '\n';
        }
        mostrarReprobados(raiz->derecho);
    }
}

// 6. Calcular el promedio de todas las notas
float calcularPromedio(Estudiante *raiz, int *contador)
{
    if(raiz ==NULL)
        return 0;
    
        float sumaIzq = calcularPromedio(raiz->izquierdo, contador);
        float sumaDer = calcularPromedio(raiz->derecho, contador);

        (*contador)++;

        return sumaIzq + raiz->nota + sumaDer;
    // Usa el contador para saber cuántos estudiantes hay
}

// 7. Encontrar al estudiante con la nota más alta
Estudiante *encontrarMejorNota(Estudiante *raiz)
{
    if(raiz ==NULL) 
        return NULL;

        Estudiante* mejor = raiz;

        Estudiante *mejorIzq = encontrarMejorNota(raiz->izquierdo);
        Estudiante *mejorDer = encontrarMejorNota(raiz->derecho);

        if(mejorIzq != NULL && mejorIzq->nota > mejor->nota)
        mejor = mejorIzq;

        if(mejorDer != NULL && mejorDer->nota > mejor->nota )
        mejor = mejorDer;

    return mejor;
    
}

int main()
{
    Estudiante *sistema = NULL;
    int opcion;
    int carnet;
    char nombre[50];
    float nota;

    do
    {
        cout << "\n===== SISTEMA DE GESTION DE ESTUDIANTES =====\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar todos los estudiantes\n";
        cout << "3. Buscar estudiante por carnet\n";
        cout << "4. Mostrar estudiantes aprobados\n";
        cout << "5. Mostrar estudiantes reprobados\n";
        cout << "6. Calcular promedio general\n";
        cout << "7. Mostrar estudiante con mejor nota\n";
        cout << "8. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Digite el carnet: ";
            cin >> carnet;

            cout << "Digite el nombre: ";
            cin >> nombre;

            cout << "Digite la nota: ";
            cin >> nota;

            sistema = insertar(sistema, carnet, nombre, nota);
            break;

        case 2:
            mostrarEstudiantes(sistema);
            break;

        case 3:
            int carnet;

            cout << "Digite el carnet: ";
            cin >> carnet;

            buscarEstudiante(sistema, carnet);
            break;

        case 4:
            mostrarAprobados(sistema);
            break;

        case 5:
            if(sistema == NULL) cout << "No hay estudiantes. \n";
            else mostrarReprobados(sistema);
            break;

        case 6:
            if(sistema == NULL ) {
                cout << "No hay estudiantes para calcular el promedio. \n";
            } else {
                int contador = 0;
                float suma = calcularPromedio(sistema, &contador);
                float promedio = (contador > 0) ? (suma/contador) : 0;
                cout<< "Promedio general: " << promedio << "(" << contador << " estudiantes) \n";
            }
            break;

        case 7:
            Estudiante *mejor = encontrarMejorNota(sistema);
            if(mejor == NULL){
                cout << "No hay estudiantes. \n";
            } else {
                cout << "Mejor estudiante: " << mejor->carnet
                     << ", nombre: " << mejor->nombre
                     << ", nota: " << mejor->nota << endl;
            }
            break;

        case 8:
            cout << "Saliendo del programa..." << endl;
            break;

        default:
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opcion != 8);

    return 0;
}