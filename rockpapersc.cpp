#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
using namespace std;

// Opciones del juego
enum Move { ROCK = 1, PAPER, SCISSORS };

// Función para convertir un movimiento a texto
string moveToString(Move move) {
    switch (move) {
        case ROCK: return "Piedra";
        case PAPER: return "Papel";
        case SCISSORS: return "Tijeras";
        default: return "Desconocido";
    }
}

// Función para determinar el ganador
// Devuelve 1 si gana el jugador, -1 si gana la IA y 0 si es empate
int determineWinner(Move playerMove, Move aiMove) {
    if (playerMove == aiMove) return 0;
    if ((playerMove == ROCK && aiMove == SCISSORS) ||
        (playerMove == PAPER && aiMove == ROCK) ||
        (playerMove == SCISSORS && aiMove == PAPER)) {
        return 1; // Jugador gana
    }
    return -1; // IA gana
}

// Estrategia básica de la IA (intenta predecir el siguiente movimiento del jugador)
Move aiStrategy(const unordered_map<Move, int>& playerHistory) {
    if (playerHistory.empty()) {
        // Si no hay historial, elige aleatoriamente
        return static_cast<Move>(rand() % 3 + 1);
    }

    // Analiza el movimiento más frecuente del jugador
    Move predictedMove = ROCK;
    int maxFrequency = 0;
    for (const auto& entry : playerHistory) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            predictedMove = entry.first;
        }
    }

    // Contrarresta el movimiento más frecuente del jugador
    switch (predictedMove) {
        case ROCK: return PAPER;      // Papel vence a Piedra
        case PAPER: return SCISSORS; // Tijeras vence a Papel
        case SCISSORS: return ROCK;  // Piedra vence a Tijeras
    }
    return ROCK; // Fallback
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Inicializa la semilla para aleatoriedad

    unordered_map<Move, int> playerHistory; // Historial de movimientos del jugador
    int playerScore = 0, aiScore = 0;

    cout << "¡Bienvenido a Piedra, Papel o Tijeras!\n";
    cout << "Opciones:\n  1. Piedra\n  2. Papel\n  3. Tijeras\n";
    cout << "Escribe el número de tu elección. El primero en llegar a 5 puntos gana.\n";

    while (playerScore < 5 && aiScore < 5) {
        // Turno del jugador
        cout << "\nTu turno: ";
        int playerInput;
        cin >> playerInput;

        // Verificar si la entrada es válida
        if (cin.fail() || playerInput < 1 || playerInput > 3) {
            cout << "Entrada inválida. Por favor, ingresa un número entre 1 y 3.\n";
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada no válida
            continue;
        }
        Move playerMove = static_cast<Move>(playerInput);

        // Turno de la IA
        Move aiMove = aiStrategy(playerHistory);

        // Mostrar movimientos
        cout << "Tú elegiste: " << moveToString(playerMove) << "\n";
        cout << "La IA eligió: " << moveToString(aiMove) << "\n";

        // Determinar el ganador
        int result = determineWinner(playerMove, aiMove);
        if (result == 1) {
            cout << "¡Ganaste esta ronda!\n";
            playerScore++;
        } else if (result == -1) {
            cout << "La IA gana esta ronda.\n";
            aiScore++;
        } else {
            cout << "¡Es un empate!\n";
        }

        // Actualizar historial del jugador
        playerHistory[playerMove]++;

        // Mostrar puntajes
        cout << "Puntaje: Tú " << playerScore << " - " << aiScore << " IA\n";
    }

    // Declarar al ganador
    if (playerScore == 5) {
        cout << "\n¡Felicidades! ¡Ganaste el juego!\n";
    } else {
        cout << "\nLa IA ganó el juego. ¡Mejor suerte la próxima vez!\n";
    }

    return 0;
}
