#ifndef PARSER_H
#define PARSER_H

#include "dataset.h"

Dataset parseDataset(std::string line, int lineNo);
std::vector<Dataset> parseFile(std::ifstream& stream);

#endif
