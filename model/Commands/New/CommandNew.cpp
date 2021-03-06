//
// Created by ahmad on 28/12/2018.
//

#include "CommandNew.h"

/*******************  init static variables *********************/
const std::string CommandNew::LENGTH_ERROR = "This command takes at the most 3 arguments new <seq> [@<name>]";

const std::string CommandNew::NAME_ERROR = "name of sequence should start with @<name> or you "
                                           "can remove it and we will set a default one for you";

const std::string CommandNew::CREATE_DEFAULT_NAME = "default name";
const std::string CommandNew::PASS = "pass";
const std::string CommandNew::SEQUENCE_DEFAULT_NAME = "@seq";


DataHandler *CommandNew::p_data_handler = DataHandler::get_instance();

/***************************************************************/


CommandNew::CommandNew() {}

CommandNew::~CommandNew() {}

std::string CommandNew::run_command(const std::vector<std::string> &vector) {

    std::string afterValidation = validate_input(vector);


    std::string name;
    std::string answer;

    /* checking for errors*/
    if (afterValidation == LENGTH_ERROR
        || afterValidation == NAME_ERROR) {
        return afterValidation;
    }

    /* getting the name of the sequence */
    name = fill_sequence_name(afterValidation, vector);

    /* lets create our sequence*/
    answer = try_to_create_sequence(name, vector[SEQUENCE_TO_CREATE_POSITION]);

    return answer;
}

std::string CommandNew::try_to_create_sequence(const std::string &_name, const std::string& _seq) {
    std::stringstream s;
    std::stringstream sId;
    try {

        std::tr1::shared_ptr<IDna> shared_dna(new DnaSequence(_seq));
        static unsigned int dnaId = 1;

        sId << dnaId;
        std::string local_dnaId = sId.str();

        std::string addResult = p_data_handler->try_to_add_data(shared_dna, _name, local_dnaId);
        std::cout << (p_data_handler->s_dataHolder["1"]).get() << std::endl;
        if (addResult != p_data_handler->DATA_EXISTS) {
            ++dnaId;
        } else {
            local_dnaId = p_data_handler->s_key_name_value_id[_name];
        }
        s << addResult
          << "\n\t";

        s << build_return_value(local_dnaId, _name, shared_dna, DEFAULT_ACCURACY);

    } catch (std::invalid_argument &msg) {
        return msg.what();
    } catch (std::bad_alloc &e) {
        throw;
    }
    return s.str();

}

/*
int main (){
    CommandNew c;
    std::vector<std::string> x ;
    x.push_back("new");
    x.push_back("AGTC");
    x.push_back("@nameHHHH");
    std::cout << c.run_command(x) << std::endl;

    std::vector<std::string> y ;
    y.push_back("new");
    y.push_back("AGTC");
    std::cout << c.run_command(y) << std::endl;


    std::vector<std::string> n ;
    n.push_back("new");
    n.push_back("AGTCs");
    std::cout << c.run_command(n) << std::endl;


    return 0;
}
*/

/*
g++ -g -ansi -pedantic -std=c++98 -Wall model/dna_code/DNA/DnaSquence.cpp
 model/dna_code/Nucleotide/Nucleotide.cpp model/Commands/New/CommandNew.cpp -o a
 */


