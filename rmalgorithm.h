#ifndef RMALGORITHM_H
#define RMALGORITHM_H

#include <Qvector>
#include <QString>
//#include <QCustomPlot>

class RMAlgorithm
{
public:
    RMAlgorithm();

    void calculatePriorities();
    bool rateMonotonic(int numTasks, int timeTask, int period, int deadline);
    int rmGarantyTest(int n, QString nameTask, int timeOfTask, int period, int deadline);

private:
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
