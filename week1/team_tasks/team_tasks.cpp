//
// Created by Virgil Legros on 13/10/2019.
//

#include <map>
#include <iostream>
#include <numeric>

using namespace std;

// Перечислимый тип для статуса задачи

/*
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;
*/
///returns the next status of the task
TaskStatus	NextStatus(TaskStatus ts) {
	switch (ts) {
		case TaskStatus::NEW:
			return TaskStatus::IN_PROGRESS;
		case TaskStatus::IN_PROGRESS:
			return TaskStatus::TESTING;
		case TaskStatus::TESTING:
			return TaskStatus::DONE;
		default:
			return TaskStatus::DONE;
	}
}
// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return tasks.at(person);
	}
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		tasks[person][TaskStatus::NEW]++;
	}
	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
			const string& person, int task_count) {
		TasksInfo updated, not_updated;
		TaskStatus ts = TaskStatus::NEW;
		int in_process = 0;
		if (!tasks.count(person)) {
			return tie(updated, not_updated);
		}
		TasksInfo& p_tasks = tasks.at(person);
		for (const auto& [status, value] : p_tasks) {
			if (status != TaskStatus::DONE) {
				in_process += value;
			}
		}
		if (task_count > in_process) {
			task_count = in_process;
		}
		while (ts != TaskStatus::DONE && task_count != 0) {
			TaskStatus next_status = NextStatus(ts);
			if (p_tasks.count(ts)) {
				if (task_count < p_tasks.at(ts)) {
					updated[next_status] = task_count;
					if(not_updated.count(ts)) {
						not_updated[ts] -= task_count;
					} else {
						not_updated[ts] = p_tasks.at(ts) - task_count;
					}
					if (p_tasks.count(next_status)) {
						not_updated[next_status] = p_tasks.at(next_status);
					}
					break;
				} else {
					updated[next_status] = p_tasks.at(ts);
					if (p_tasks.count(next_status)) {
						if (task_count - p_tasks.at(ts) < p_tasks.at(next_status))
							not_updated[next_status] = p_tasks.at(next_status);
					}
					task_count -= p_tasks.at(ts);
					p_tasks.erase(ts);
					ts = next_status;
				}
			} else {
				ts = next_status;
			}
		}
		for (const auto& [status, value] : not_updated) {
			p_tasks[status] = value;
		}
		for (const auto& [status, value] : updated) {
			p_tasks[status] += value;
		}
		for (const auto& [status, value] : p_tasks) {
			if (!not_updated.count(status) && !updated.count(status)) {
				not_updated[status] = value;
			}
		}
		not_updated.erase(TaskStatus::DONE);
		return tie(updated, not_updated);
	}
private:
	map<string, TasksInfo> tasks;
};

void PrintTasksInfo(TasksInfo tasks_info) {
	for (const auto& [status, amount] : tasks_info) {
		cout << "(" << static_cast<int>(status) << " " << amount << ")" << " ";
	}
	cout << endl;
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		 ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		 ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		 ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}
/*
int 	main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << endl;
	TasksInfo updated_tasks, untouched_tasks;
	///1///
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << endl;
	////2////
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
	cout << endl;
	return 0;
}


int main() {

	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	///1///
	cout << "1" << endl;
	TasksInfo updated_tasks, untouched_tasks;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;
	///2///
	cout << "2" << endl;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 5);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;
	///3///
	cout << "3" << endl;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 1);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;
	///4///
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	cout << "4" << endl;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;
	///5///
	cout << "5" << endl;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 4);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;
	return 0;
}
*/