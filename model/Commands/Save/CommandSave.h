//
// Created by ahmad on 04/01/2019.
//

#ifndef PROJECT_DNA_ANALYZER_SAVE_H
#define PROJECT_DNA_ANALYZER_SAVE_H


#include "../../dna_code/DataHandler/DataHandler.h"
#include "../../dna_code/Dna_reader_writer/Dna_writer/Dna_writer.h"
#include "../DataAccessPermissionCommands.h"

class CommandSave : public DataAccessPermissionCommands{

    static DataHandler * p_data_handler;
    static Dna_writer* p_dna_writer;

public:

    CommandSave();

    static const std::string FILE_SUFFIX;
    static const std::string INVALID_INPUT;
    static const std::string PASS;

    std::string run_command(const std::vector<std::string> &vector);

private:

    inline const std::string &validate_input(const std::vector<std::string> &vector);

    std::string try_to_get_sequence_and_save(const std::vector<std::string> &vector);
    std::string try_to_save(std::pair<std::string, std::tr1::shared_ptr<IDna> > pair, const std::vector<std::string> &vector);
};

const std::string &CommandSave::validate_input(const std::vector<std::string> &vector) {
    if (vector.size() > 3 || vector.size() < 2)
        return INVALID_INPUT;

    if (!validate_name_or_id(vector[1][0]))
        return INVALID_INPUT;
    return PASS;

}

#endif //PROJECT_DNA_ANALYZER_SAVE_H
