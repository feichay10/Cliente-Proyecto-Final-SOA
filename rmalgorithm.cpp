#include "rmalgorithm.h"

RMAlgorithm::RMAlgorithm(QTableWidget* tableTasks) {
  if (tableTasks != NULL) {
    for(int i{0}; i < tableTasks->rowCount(); ++i) {
      Task current_task{tableTasks->item(i, 0)->text(), i + 1, std::stoi(tableTasks->item(i, 1)->text().toStdString()), std::stoi(tableTasks->item(i, 2)->text().toStdString()), std::stoi(tableTasks->item(i, 3)->text().toStdString()), std::stoi(tableTasks->item(i, 1)->text().toStdString()), 0, 0, true};
      tasks_.push_back(current_task);
    }

    std::sort(tasks_.begin(), tasks_.end(), [] (const Task & task_a, const Task & task_b) {
      return task_a.period < task_b.period;
    });
  }
}

QCustomPlot* RMAlgorithm::rateMonotonic() {
  const int kGarantyTest{garantyTest()};
  QCustomPlot* graph = NULL;

  if (kGarantyTest == 0 ||  kGarantyTest == 1) {
    int current_time = 0, max_time = 120;
    graph = new QCustomPlot();
    //QVector<double> x(max_time); ///<time pos
    //QVector<double> y(max_time); ///<task executed at that time
    graph->addGraph();
    graph->xAxis->setLabel("Time");
    graph->yAxis->setLabel("Task executed");
    graph->xAxis->setRange(0, max_time);
    graph->yAxis->setRange(0, tasks_.size() + 1);
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

    for (int i = 0; i < tasks_.size(); ++i)
      textTicker->addTick(i + 1, tasks_[i].name);

    graph->yAxis->setTicker(textTicker);
    //for (double d = 0.0; d < 120.0; d += 0.01)
    //graph->graph(0)->addData(d, 0.0);
    Task* current_task = NULL;
    std::list<Task*> runnable_tasks;

    while (current_time < max_time) {
      std::cout << "T: " << current_time;

      for (int i = 0; i < tasks_.size(); ++i) {
        if (tasks_[i].just_arrived && (tasks_[i].last_entry_point + tasks_[i].period <= current_time || tasks_[i].exec_num == 0)) {
          runnable_tasks.push_back(&tasks_[i]);
          tasks_[i].last_entry_point = current_time;
          tasks_[i].just_arrived = false;
        }
      }

      if (!runnable_tasks.empty()) {
        runnable_tasks.sort([] (Task * task_a, Task * task_b) {
          return task_a->period < task_b->period;
        });

        if (current_task == NULL || current_task->period > runnable_tasks.front()->period) {
          if (current_task != NULL) runnable_tasks.push_back(current_task);

          current_task = runnable_tasks.front();
          runnable_tasks.pop_front();
        }
      }

      if (current_task != NULL) {
        std::cout << " - Executing " << current_task->name.toStdString() << current_task->exec_num << " remaining time: " << current_task ->remaining_time;
        //x[current_time] = current_time;
        //y[current_time] = current_task->graph_pos;
        graph->graph(0)->addData((double)current_time, (double)current_task->graph_pos);
        //std::cout << " entered processor in: " << current_task->last_entry_point;
        current_task->remaining_time--;

        if (current_task->remaining_time == 0) {
          current_task->remaining_time = current_task->timeTask;
          current_task->exec_num++;
          current_task->just_arrived = true;
          current_task = NULL;
        }
      }

      std::cout << std::endl;
      ++current_time;
    }

    //graph->graph(0)->setData(x, y);
    graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    graph->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    //graph->graph(0)->setLinePen(QPen(Qt::red, 2, Qt::DashLine));
    graph->graph(0)->setPen(QPen(Qt::magenta, 2, Qt::DashLine));
  }

  return graph;
}

int RMAlgorithm::garantyTest() {
  if (tasks_.size() > 0) {
    double upper_limit = tasks_.size() * (pow(2, 1 / (double)tasks_.size()) - 1);
    double use_factor = 0.0;

    for (const auto& task : tasks_)
      use_factor += task.timeTask / (double)task.period;

    if (use_factor <= upper_limit) {
      return 0; ///<Planificable

    } else if (use_factor < 1.00) {
      return 1; ///<Success not guaranteed

    } else return 2; ///<Overload
  }

  return -1; ///<No tasks
}
