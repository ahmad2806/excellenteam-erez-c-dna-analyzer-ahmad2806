//
// Created by ahmad on 28/12/2018.
//

#ifndef PROJECT_DNA_ANALYZER_COMMAND_H
#define PROJECT_DNA_ANALYZER_COMMAND_H

#include <iostream>
class Command{
public:
    virtual std::string run_command() = 0;
    virtual ~Command(){};
};
#endif //PROJECT_DNA_ANALYZER_COMMAND_H
