//
// Created by Virgil Legros on 13/10/2019.
//

#include <map>
#include <iostream>

using namespace std;

// Перечислимый тип для статуса задачи


enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

TaskStatus	NextTaskStatus(const TaskStatus value) {
	switch (value) {
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

void 	EraseZero(TasksInfo& tasks, TaskStatus TS) {
	if (tasks.count(TS)) {
		if (!tasks.at(TS))
			tasks.erase(TS);
	}
}

void 	EraseZeroes(TasksInfo& tasks) {
	EraseZero(tasks, TaskStatus::NEW);
	EraseZero(tasks, TaskStatus::IN_PROGRESS);
	EraseZero(tasks, TaskStatus::TESTING);
	EraseZero(tasks, TaskStatus::DONE);
}

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
		TasksInfo changed, not_changed;
		TasksInfo& PersonsTasks = tasks.at(person);
		int in_progress = 0;
		for (const auto& [key, value] : tasks[person]) {
			in_progress += value;
		}
		if (task_count > in_progress) {
			task_count = in_progress;
		}
		for (auto& [status, value] : PersonsTasks) {
			TaskStatus NextStatus = NextTaskStatus(status);
			if (task_count < value) {
				changed[NextStatus] = task_count;
				not_changed[status] = value - task_count;
				value -= task_count;
				break ;
			} else {
				changed[NextStatus] = value;
				not_changed.erase(status);
				task_count -= value;
				value = 0;
			}
			if (PersonsTasks.count(NextStatus)) {
				not_changed[NextStatus] = PersonsTasks.at(NextStatus);
			}
		}
		for (const auto& [status, value] : changed) {
			tasks[person][status] = value + not_changed[status];
		}
		EraseZeroes(PersonsTasks);
		return tie(changed, not_changed);
	}
	void PrintTasks() {
		for (const auto& [person, task] : tasks) {
			cout << person << " ";
			for (const auto& [status, amount] : task) {
				cout << "(" << static_cast<int>(status) << " " << amount << ")" << " ";
			}
			cout << endl;
		}
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


int main() {
	TeamTasks tasks;
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;

	TasksInfo updated_tasks, untouched_tasks;
	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Alice", 2);
	cout << "Updated Alice's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Alice's tasks: ";
	PrintTasksInfo(untouched_tasks);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	cout << endl;

	/*tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tasks.PerformPersonTasks("Alice", 2);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	return 0;*/
}