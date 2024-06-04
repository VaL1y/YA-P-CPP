#include "CodeModel.h"
#include <limits>

// Helper functions for clearing the input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void generateDefaultCode() {
    Namespace ns("MyNamespace");

    auto baseClass = std::make_shared<Class>("BaseClass");
    baseClass->addMethod(Method("AbstractMethod", "void", true));
    ns.addClass(baseClass);

    auto derivedClass = std::make_shared<Class>("DerivedClass", "BaseClass");
    derivedClass->addField(Field("myField", "int"));
    derivedClass->addMethod(Method("ConcreteMethod", "void"));
    derivedClass->addProperty(Property("MyProperty", "int"));
    ns.addClass(derivedClass);

    // Validate classes
    baseClass->validate();
    derivedClass->validate();

    // Generate code
    std::cout << ns.generateCode() << std::endl;
}

void createNamespace(std::vector<std::shared_ptr<Namespace>> &namespaces) {
    std::string name;
    std::cout << "Enter namespace name: ";
    std::cin >> name;
    namespaces.push_back(std::make_shared<Namespace>(name));
}

void createClass(std::shared_ptr<Namespace> &ns) {
    std::string name, baseClass;
    std::cout << "Enter class name: ";
    std::cin >> name;
    std::cout << "Enter base class name (leave empty if none): ";
    std::cin.ignore();
    std::getline(std::cin, baseClass);
    ns->addClass(std::make_shared<Class>(name, baseClass));
}

void createField(std::shared_ptr<Class> &cls) {
    std::string name, type;
    std::cout << "Enter field name: ";
    std::cin >> name;
    std::cout << "Enter field type: ";
    std::cin >> type;
    cls->addField(Field(name, type));
}

void createMethod(std::shared_ptr<Class> &cls) {
    std::string name, returnType;
    char isAbstractChar;
    bool isAbstract = false;
    std::cout << "Enter method name: ";
    std::cin >> name;
    std::cout << "Enter return type: ";
    std::cin >> returnType;
    std::cout << "Is it abstract? (y/n): ";
    std::cin >> isAbstractChar;
    isAbstract = (isAbstractChar == 'y' || isAbstractChar == 'Y');
    cls->addMethod(Method(name, returnType, isAbstract));
}

void createProperty(std::shared_ptr<Class> &cls) {
    std::string name, type;
    std::cout << "Enter property name: ";
    std::cin >> name;
    std::cout << "Enter property type: ";
    std::cin >> type;
    cls->addProperty(Property(name, type));
}

void listNamespaces(const std::vector<std::shared_ptr<Namespace>> &namespaces) {
    std::cout << "Namespaces:" << std::endl;
    for (const auto &ns: namespaces) {
        std::cout << "  " << ns->getName() << std::endl;
    }
}

void listClasses(const std::shared_ptr<Namespace> &ns) {
    std::cout << "Classes in namespace " << ns->getName() << ":" << std::endl;
    for (const auto &cls: ns->getClasses()) {
        std::cout << "  " << cls->getName() << std::endl;
    }
}

int main() {
    std::vector<std::shared_ptr<Namespace>> namespaces;
    int choice;
    std::shared_ptr<Namespace> currentNamespace = nullptr;
    std::shared_ptr<Class> currentClass = nullptr;
    std::string nsName, clsName;

    while (true) {
        std::cout << "0. Generate Default Code" << std::endl;
        std::cout << "1. Create Namespace" << std::endl;
        std::cout << "2. Select Namespace" << std::endl;
        std::cout << "3. Create Class" << std::endl;
        std::cout << "4. Select Class" << std::endl;
        std::cout << "5. Create Field" << std::endl;
        std::cout << "6. Create Method" << std::endl;
        std::cout << "7. Create Property" << std::endl;
        std::cout << "8. Generate Code" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                generateDefaultCode();
                break;
            case 1:
                createNamespace(namespaces);
                break;
            case 2:
                listNamespaces(namespaces);
                std::cout << "Enter namespace name to select: ";
                std::cin >> nsName;
                currentNamespace = nullptr;
                for (auto &ns: namespaces) {
                    if (ns->getName() == nsName) {
                        currentNamespace = ns;
                        break;
                    }
                }
                if (!currentNamespace) {
                    std::cout << "Namespace not found!" << std::endl;
                }
                break;
            case 3:
                if (currentNamespace) {
                    createClass(currentNamespace);
                } else {
                    std::cout << "No namespace selected!" << std::endl;
                }
                break;
            case 4:
                if (currentNamespace) {
                    listClasses(currentNamespace);
                    std::cout << "Enter class name to select: ";
                    std::cin >> clsName;
                    currentClass = currentNamespace->getClass(clsName);
                    if (!currentClass) {
                        std::cout << "Class not found!" << std::endl;
                    }
                } else {
                    std::cout << "No namespace selected!" << std::endl;
                }
                break;
            case 5:
                if (currentClass) {
                    createField(currentClass);
                } else {
                    std::cout << "No class selected!" << std::endl;
                }
                break;
            case 6:
                if (currentClass) {
                    createMethod(currentClass);
                } else {
                    std::cout << "No class selected!" << std::endl;
                }
                break;
            case 7:
                if (currentClass) {
                    createProperty(currentClass);
                } else {
                    std::cout << "No class selected!" << std::endl;
                }
                break;
            case 8:
                for (const auto &ns: namespaces) {
                    std::cout << ns->generateCode() << std::endl;
                }
                break;
            case 9:
                return 0;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
        }
    }
}
