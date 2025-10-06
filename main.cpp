#include <iostream>
#include <sstream>
#include <string> // CORRECCIÓN 1: Incluir la librería para usar 'string'.

// --- Declaraciones de funciones ---
void addPackage();
void dispatchPackage();
void incrementCapacity();
void inspectFront();
void reportDestiny();
void liberarMemoria(); // CORRECCIÓN 2: El nombre debe ser consistente.
std::string priorityAText(int p); // CORRECCIÓN 3: Declarar la función para que 'inspectFront' la conozca.

// --- Variables Globales ---
int *idPackage = nullptr;
double *weigth = nullptr;
std::string *destiny = nullptr; // Se recomienda usar std::string
int *priority = nullptr;
char *state = nullptr;

int capacity = 50;
int front = 0;
int packagesOnSystem = 0;
int packageOnWait = 0;

int main() {
    int opcion;

    idPackage = new int[capacity];
    weigth = new double[capacity];
    destiny = new std::string[capacity];
    priority = new int[capacity];
    state = new char[capacity];
    
    do
    {
        std::cout << "-- Seleccione una operación --" << std::endl; 
        std::cout << "1. Agregar Paquete (Encolar)" << std::endl; 
        std::cout << "2. Despachar Paquete (Desencolar)" << std::endl; 
        std::cout << "3. Inspeccionar Frente de Cola" << std::endl; 
        std::cout << "4. Reporte por Destino" << std::endl; 
        std::cout << "5. Salir (Liberar Memoria)" << std::endl; 
        std::cout << "Opcion: ";
        std::cin >> opcion;
        switch (opcion)
        {
            case 1:
                addPackage();
                break;
            case 2:
                dispatchPackage(); 
                break;
            case 3:
                inspectFront();
                break;
            case 4:
                reportDestiny();
                break;
            case 5:
                liberarMemoria(); 
                std::cout << "Saliendo...." << std::endl;
                break;
            default:
                std::cout << "- Opcion invalida. Intente de nuevo -" << std::endl;
                break;
        }
    } while (opcion != 5 );
    return 0;
}

void liberarMemoria() {
    std::cout << "Liberando " << capacity << " bloques de memoria asignada..." << std::endl;
    delete[] idPackage;
    delete[] weigth;
    delete[] destiny;
    delete[] priority;
    delete[] state;
    
    idPackage = nullptr;
    weigth = nullptr;
    destiny = nullptr;
    priority = nullptr;
    state = nullptr;
    std::cout << "Sistema cerrado. ¡Memoria libre!" << std::endl;
}

void reportDestiny() {
    if (packageOnWait == 0) {
        std::cout << "No hay paquetes en cola para generar un reporte." << std::endl;
        return;
    }

    std::string searchDestiny;
    std::cout << "Ingrese el destino para el reporte: ";
    std::cin.ignore();
    std::getline(std::cin, searchDestiny);

    int destinyCount = 0;
    float totalDestinyWeigth = 0.0f;

    for (int i = front; i < packagesOnSystem; ++i) {
        if (state[i] == 'E' && destiny[i] == searchDestiny) {
            destinyCount++;
            totalDestinyWeigth += weigth[i];
        }
    }
    
    std::cout << "Reporte para destino '" << searchDestiny << "':" << std::endl;
    if (destinyCount > 0) {
        float promWeigth = totalDestinyWeigth / destinyCount;
        std::cout << "  Paquetes En Cola: " << destinyCount << std::endl;
        std::cout << "  Peso Promedio: " << promWeigth << " kg" << std::endl;
    } else {
        std::cout << "  No se encontraron paquetes en cola para este destino." << std::endl;
    }
}

void dispatchPackage(){
    if (packageOnWait == 0) {
        std::cout << "No hay paquetes en la cola para despachar." << std::endl;
        return;
    }

    std::cout << "Despachando paquete..." << std::endl;
    state[front] = 'D';
    std::cout << "Paquete " << idPackage[front] << " despachado con éxito. Estado: 'D'." << std::endl;
    
    front++;
    packageOnWait--;
}

void inspectFront(){
     if (packageOnWait == 0) {
        std::cout << "La cola está vacía." << std::endl;
        return;
    }

    std::cout << "Frente de la cola:" << std::endl;
    std::cout << "  ID: " << idPackage[front] << " | Peso: " << weigth[front]
              << " kg | Destino: " << destiny[front] << " | Prioridad: " << priorityAText(priority[front]) << std::endl;
}

std::string priorityAText(int p) {
    switch (p) {
        case 1: return "Alta";
        case 2: return "Media";
        case 3: return "Baja";
        default: return "Desconocida";
    }
}

void addPackage(){
    if (packagesOnSystem == capacity)
    {
        incrementCapacity();
    }
    int id, prioridad;
    double peso;
    std::string destino;

    std::cout << "Ingrese ID: ";
    std::cin >> id;
    std::cout << "Ingrese Peso (kg): ";
    std::cin >> peso;
    std::cout << "Ingrese Destino: ";
    std::cin.ignore();
    std::getline(std::cin, destino);
    
    std::cout << "Ingrese Prioridad (1=Alta, 2=Media, 3=Baja): ";
    std::cin >> prioridad;

    int indice = packagesOnSystem;
    idPackage[indice] = id;
    weigth[indice] = peso;
    destiny[indice] = destino;
    priority[indice] = prioridad;
    state[indice] = 'E'; 

    packagesOnSystem++;
    packageOnWait++;

    std::cout << "Paquete " << id << " encolado. Capacidad utilizada: " << packagesOnSystem << "/" << capacity << "." << std::endl;
}

void incrementCapacity(){
    int *ptr_aux_idPackage = new int[capacity + 1];
    double *ptr_aux_weigth = new double[capacity + 1];
    std::string *ptr_aux_destiny = new std::string[capacity + 1];
    int *ptr_aux_priority = new int[capacity + 1];
    char *ptr_aux_state = new char[capacity + 1];
    
    for (int i = 0; i < capacity; i++) {
        ptr_aux_idPackage[i] = idPackage[i];
        ptr_aux_weigth[i] = weigth[i];
        ptr_aux_destiny[i] = destiny[i];
        ptr_aux_priority[i] = priority[i];
        ptr_aux_state[i] = state[i];
    }
    
    delete[] idPackage;
    delete[] weigth;
    delete[] destiny;
    delete[] priority;
    delete[] state;

    idPackage = ptr_aux_idPackage;
    weigth = ptr_aux_weigth;
    destiny = ptr_aux_destiny;
    priority = ptr_aux_priority;
    state = ptr_aux_state;

    capacity++;
}