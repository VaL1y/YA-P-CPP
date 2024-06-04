//
// Created by Валерий on 04.06.2024.
//

#ifndef TASK_2_5_CPP_CODEMODEL_H
#define TASK_2_5_CPP_CODEMODEL_H
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Field;

class Method;

class Property;

class Class {
public:
    Class(const std::string &name, const std::string &baseClass = "");

    void addField(const Field &field);

    void addMethod(const Method &method);

    void addProperty(const Property &property);

    void setBaseClass(const std::string &baseClass);

    void validate() const;

    std::string generateCode() const;

    std::string getName() const;

private:
    std::string name;
    std::string baseClass;
    std::vector<Field> fields;
    std::vector<Method> methods;
    std::vector<Property> properties;
};

class Namespace {
public:
    Namespace(const std::string &name);

    void addClass(const std::shared_ptr<Class> &cls);

    std::shared_ptr<Class> getClass(const std::string &name) const;

    std::vector<std::shared_ptr<Class>> getClasses() const;

    std::string generateCode() const;

    std::string getName() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Class>> classes;
};

class Field {
public:
    Field(const std::string &name, const std::string &type);

    std::string generateCode() const;

private:
    std::string name;
    std::string type;
};

class Method {
public:
    Method(const std::string &name, const std::string &returnType, bool isAbstract = false);

    std::string generateCode() const;

    bool isAbstract() const;

private:
    std::string name;
    std::string returnType;
    bool abstract;
};

class Property {
public:
    Property(const std::string &name, const std::string &type);

    std::string generateCode() const;

private:
    std::string name;
    std::string type;
};

#endif //TASK_2_5_CPP_CODEMODEL_H
