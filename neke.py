import json

class Student:
    """
    This is a docstring for MyClass.

    You can provide a description of what this class does here.
    """
    def __init__(self, id, name, mail):
        self.id = id
        self.name = name
        self.mail = mail

    def get_id(self):
        """A public method to retrieve the value."""
        return self.id

    def set_id(self, new_id):
        """A public method to set a new value."""
        self.id = new_id

students = []

with open('data.json', 'r', encoding='utf-8') as file:
    data = json.load(file)
    student_data = data["data"]

    for item in student_data:
        student = Student(item["id"], item["Name"], item["Mail"])
        students.append(student)

for s in students:
    print(s.id)
    print(s.name)
    print(s.mail + "\n")
