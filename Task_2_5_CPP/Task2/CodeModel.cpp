//
// Created by Валерий on 04.06.2024.
//
#include "CodeModel.h"

// Class methods
Class::Class(const std::string &name, const std::string &baseClass)
        : name(name), baseClass(baseClass) {}

void Class::addField(const Field &field) {
    fields.push_back(field);
}

void Class::addMethod(const Method &method) {
    methods.push_back(method);
}

void Class::addProperty(const Property &property) {
    properties.push_back(property);
}

void Class::setBaseClass(const std::string &baseClass) {
    this->baseClass = baseClass;
}

void Class::validate() const {
    if (!baseClass.empty()) {
        std::cout << "Validating class: " << name << " which inherits from " << baseClass << std::endl;
        for (const auto &method: methods) {
            if (method.isAbstract()) {
                std::cerr << "Error: Abstract method " << method.generateCode() << " not implemented in class " << name
                          << std::endl;
            }
        }
    }
}

std::string Class::generateCode() const {
    std::string code = "class " + name;
    if (!baseClass.empty()) {
        code += " : public " + baseClass;
    }
    code += " {\npublic:\n";
    for (const auto &field: fields) {
        code += "    " + field.generateCode() + ";\n";
    }
    for (const auto &method: methods) {
        code += "    " + method.generateCode() + ";\n";
    }
    for (const auto &property: properties) {
        code += "    " + property.generateCode() + ";\n";
    }
    code += "};\n";
    return code;
}

std::string Class::getName() const {
    return name;
}

// Namespace methods
Namespace::Namespace(const std::string &name)
        : name(name) {}

void Namespace::addClass(const std::shared_ptr<Class> &cls) {
    classes.push_back(cls);
}

std::shared_ptr<Class> Namespace::getClass(const std::string &name) const {
    auto it = std::find_if(classes.begin(), classes.end(),
                           [&name](const std::shared_ptr<Class> &cls) { return cls->getName() == name; });
    return (it != classes.end()) ? *it : nullptr;
}

std::vector<std::shared_ptr<Class>> Namespace::getClasses() const {
    return classes;
}

std::string Namespace::generateCode() const {
    std::string code = "namespace " + name + " {\n";
    for (const auto &cls: classes) {
        code += cls->generateCode() + "\n";
    }
    code += "}\n";
    return code;
}

std::string Namespace::getName() const {
    return name;
}

// Field methods
Field::Field(const std::string &name, const std::string &type)
        : name(name), type(type) {}

std::string Field::generateCode() const {
    return type + " " + name;
}

// Method methods
Method::Method(const std::string &name, const std::string &returnType, bool isAbstract)
        : name(name), returnType(returnType), abstract(isAbstract) {}

std::string Method::generateCode() const {
    return returnType + " " + name + "()";
}

bool Method::isAbstract() const {
    return abstract;
}

// Property methods
Property::Property(const std::string &name, const std::string &type)
        : name(name), type(type) {}

std::string Property::generateCode() const {
    return type + " " + name + " { get; set; }";
}
