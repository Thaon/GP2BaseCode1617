#ifndef _COMMAND_LINE_PARSER_H
#define _COMMAND_LINE_PARSER_H

#include "OptionParser.h"

class CommandLineParser:public OptionParser
{
public:
  CommandLineParser(int argc,char * argv[]);
  ~CommandLineParser();

  void parse(ProgramOptions &options);
private:
  std::vector<std::string> m_CommandArguments;
};
#endif
