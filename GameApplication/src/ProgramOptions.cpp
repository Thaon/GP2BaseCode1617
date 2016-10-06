#include "ProgramOptions.h"

std::ostream& operator<<(std::ostream& os, ProgramOptions& options)
{
    auto begin=options.begin();
    auto end=options.end();
    for(auto iter=begin;iter!=end;++iter)
    {
      os<<iter->first<<" = "<<iter->second<<" ";
    }
    return os;
}

ProgramOptions::ProgramOptions()
{

}

ProgramOptions::~ProgramOptions()
{
  m_options.clear();
}

void ProgramOptions::addOption(const std::string& name, const std::string& value)
{
  m_options[name]=value;
}

const std::string& ProgramOptions::getOption(const std::string& name)
{
  return m_options[name];
}

float ProgramOptions::getOptionAsFloat(const std::string& name)
{
  return stof(m_options[name]);
}

int ProgramOptions::getOptionAsInt(const std::string& name)
{
    return stoi(m_options[name]);
}

bool ProgramOptions::getOptionAsBool(const std::string& name)
{
    return (bool)stoi(m_options[name]);
}
