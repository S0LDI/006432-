#include <iostream>
#include <vector>
#include <algorithm> // для використання std::find

class Worker {
protected:
    std::string name;
    std::string department; // додали поле для відділу
public:
    Worker(std::string n) : name(n), department("Unassigned") {}

    std::string getName() const {
        return name;
    }

    std::string getDepartment() const {
        return department;
    }

    void setDepartment(const std::string& newDepartment) {
        department = newDepartment;
    }
};

class Department {
private:
    std::vector<Worker*> workers;

public:
    // Додали метод, який додає працівника в відділ
    void add(Worker* worker) {
        workers.push_back(worker);
        std::cout << worker->getName() << " приєднався до відділу " << worker->getDepartment() << "\n";
    }

    // Метод для виводу інформації про працівників в відділі
    void showWorkers() const {
        std::cout << "Працівники в відділі:\n";
        for (const auto& worker : workers) {
            std::cout << worker->getName() << " (" << worker->getDepartment() << ")\n";
        }
    }

    // Переведення працівника в інший відділ
    void transfer(Worker* worker, const std::string& newDepartment) {
        std::cout << worker->getName() << " переведений в відділ " << newDepartment << "\n";
        worker->setDepartment(newDepartment);
    }

    // Деструктор для вивільнення пам'яті
    ~Department() {
        for (auto& worker : workers) {
            delete worker;
        }
    }
};

int main() {
    // Створюємо працівників поза областю видимості класу Department
    Worker* w1 = new Worker("Антін");
    Worker* w2 = new Worker("Івасик");
    Worker* w3 = new Worker("Євген");
    Worker* w4 = new Worker("Їржик");

    {
        // Створюємо відділ і передаємо працівників як параметри конструктора
        Department department; // створюємо пустий відділ

        department.add(w1);
        department.add(w2);
        department.add(w3);

        department.showWorkers();

        // Переведення працівника в інший відділ
        department.transfer(w2, "HR");

        department.showWorkers();
    } // department виходить з області видимості і знищується тут

    // Після розформування відділу працівники продовжують працювати
    std::cout << w1->getName() << " досі працює у відділі " << w1->getDepartment() << "\n";
    std::cout << w2->getName() << " досі працює у відділі " << w2->getDepartment() << "\n";
    std::cout << w3->getName() << " досі працює у відділі " << w3->getDepartment() << "\n";

    // Переведення працівника в інший відділ після розформування
    Department newDepartment;
    newDepartment.transfer(w1, "IT");

    // Зміна кольору кузова другого автомобіля
    std::cout << "\nПрацівники після переведення в інший відділ:\n";
    newDepartment.showWorkers();

    delete w1;
    delete w2;
    delete w3;
    delete w4;

    return 0;
}
