#include <iostream>

using namespace std;

namespace simpleMVC {

struct Student {
  string name;
  string id;

  Student(const string& name, const string& id) : name(name), id(id) {}
};

class StudentView {
 public:
  void print_student_details(string name, string id) {
    cout << "[Student " + id + "] " + name << endl;
  }
};

struct StudentController {
  StudentController(Student student, StudentView view)
      : student(student), view(view) {}

  void updateView() { view.print_student_details(student.name, student.id); }

  void set_student_name(string name) { student.name = name; }

  string get_student_name() { return student.name; }

 private:
  Student student;
  StudentView view;
};

void main(void) {
  cout << "[simpleMVC]" << endl;

  Student student("Tom", "s115");
  StudentView view;

  StudentController controller(student, view);
  controller.updateView();
  controller.set_student_name("Tam");
  controller.updateView();

  cout << endl;
}
}  // namespace simpleMVC

int main(void) {
  simpleMVC::main();
  return 0;
}