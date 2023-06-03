#ifndef RMALGORITHM_H
#define RMALGORITHM_H

#include <Qvector>
#include <QString>

class RMAlgorithm
{
public:
    RMAlgorithm();

    void calculatePriorities();
    bool rateMonotonic(int numTasks, int timeTask, int period, int deadline);
    bool rmGarantyTest(int n, QString nameTask, int timeOfTask, int period, int deadline);

private:
    // Temporarily table
    struct Task {
        int timeTask;
        int period;
        int deadline;
    }

    QVector<Task> tasks;

    float worst_case;
    float utilization;
};

#endif // RMALGORITHM_H
