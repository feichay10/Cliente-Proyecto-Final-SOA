#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
    if (tableTasks != NULL) {
        for(int i{0}; i < tableTasks->rowCount(); ++i) {
            Task current_task{tableTasks->item(i,0)->text(), std::stoi(tableTasks->item(i,1)->text().toStdString()), std::stoi(tableTasks->item(i,2)->text().toStdString()), std::stoi(tableTasks->item(i,3)->text().toStdString())};
            tasks_.push_back(current_task);
        }
    }
}

bool RMAlgorithm::rateMonotonic() {
    if (tasks_.size() > 0 && isSchedulable()) {
        return true;
    } else {
        return false;
    }
}

// U_0 -> worst_case, U -> utilization
// Si U_0 ≤ U ≤ U_0(N) => Se puede planificar
// Si U_0(N) ≤ U ≤ 1 => No garantizado
// Si 1 ≤ U => Sobrecarga
bool RMAlgorithm::isSchedulable() {
    /*worst_case_ = ((double)n * (pow(2.0, 1.0/(double)n) - 1.0));
    utilization_ = 0.0;

    ///< Garanty Test
    if (utilization <= worst_case) {
        return 1; // Planificable
    } else if (worst_case <= utilization && utilization <= 1) {
        return 2; // Not garanty
    } else if (1 <= utilization) {
        return 3; // Overload
    }*/
    return true;
}

