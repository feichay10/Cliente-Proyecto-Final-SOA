#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
    if (tableTasks != NULL) {
        for(int i{0}; i < tableTasks->rowCount(); ++i) {
            Task current_task{tableTasks->item(i,0)->text(), std::stoi(tableTasks->item(i,1)->text().toStdString()), std::stoi(tableTasks->item(i,2)->text().toStdString()), std::stoi(tableTasks->item(i,3)->text().toStdString())};
            tasks_.push_back(current_task);
        }
        std::sort(tasks_.begin(), tasks_.end(), [] (const Task& task_a, const Task& task_b) {return task_a.period < task_b.period;});
    }
}

void RMAlgorithm::rateMonotonic() {
    const int kGarantyTest{garantyTest()};
    if (kGarantyTest == 0 ||  kGarantyTest == 1) {

    }
}

// U_0 -> worst_case, U -> utilization
// Si U_0 ≤ U ≤ U_0(N) => Se puede planificar
// Si U_0(N) ≤ U ≤ 1 => No garantizado
// Si 1 ≤ U => Sobrecarga
int RMAlgorithm::garantyTest() {
    /*double worst_case{((double)n * (pow(2.0, 1.0/(double)n) - 1.0))};
    double utilization{0.0};

    if (tasks_.size() <= 0) {
        return -1; ///< No tasks :(
    } else if (utilization <= worst_case) {
        return 0; ///< Planificable
    } else if (worst_case <= utilization && utilization <= 1) {
        return 1; ///< Not garanty
    } else if (1 <= utilization) {
        return 2; ///< Overload
    }*/
    return 0;
}
