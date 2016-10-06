#ifndef _PROGRAm_options_H
#define _PROGRAm_options_H

#include "Common.h"

class ProgramOptions
{
public:
  ProgramOptions();
  ~ProgramOptions();

  void addOption(const std::string& name, const std::string& value);
  const std::string& getOption(const std::string& name);
  float getOptionAsFloat(const std::string& name);
  int getOptionAsInt(const std::string& name);
  bool getOptionAsBool(const std::string& name);
  std::map<std::string,std::string>::iterator begin()
  {
    return m_options.begin();
  };

  std::map<std::string,std::string>::iterator end()
  {
    return m_options.end();
  };

  friend std::ostream& operator<<(std::ostream& os, ProgramOptions& options);
private:
  std::map<std::string,std::string> m_options;
};
#endif
