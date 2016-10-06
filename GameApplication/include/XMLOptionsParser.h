#ifndef _XML_OPTIONS_PARSER_H
#define _XML_OPTIONS_PARSER_H

#include "Common.h"
#include "OptionParser.h"

class XMLOptionsParser:public OptionParser
{
public:
  XMLOptionsParser(const std::string& filename);
  ~XMLOptionsParser();

  void parse(ProgramOptions &options);
private:
  std::string m_Filename;
};

#endif
