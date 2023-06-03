#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm()
{

}

void RMAlgorithm::calculatePriorities() {

}

bool RMAlgorithm::rateMonotonic(int numTasks, int timeTask, int period, int deadline) {

}

// U_0 -> worst_case, U -> utilization
// Si U_0 ≤ U ≤ U_0(N) => Se puede planificar
// Si U_0(N) ≤ U ≤ 1 => No garantizado
// Si 1 ≤ U => Sobrecarga
int RMAlgorithm::rmGarantyTest(int n, QString nameTask, int timeOfTask, int period, int deadline) {
    worst_case = ((float)n * (pow(2.0, 1.0/(float)n) - 1.0));
    utilization = 0.0;

    ///< Garanty Test
    if (utilization <= worst_case) {
        return 1; // Planificable
    } else if (worst_case <= utilization && utilization <= 1) {
        return 2; // Not garanty
    } else if (1 <= utilization) {
        return 3; // Overload
    }
}

