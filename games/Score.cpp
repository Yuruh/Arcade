//
// Score.cpp for cpp_arcade in /home/archie/workspace/C++/cpp_arcade/core/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Mar 18 09:43:25 2016 Corentin Descamps
// Last update Fri Mar 18 17:34:41 2016 Wasta-Geek
//

#include  "Score.hpp"

static bool sort_vector(Tuple<std::string, int> a, Tuple<std::string, int> b)
{
  return (a.b > b.b);
}

Score::Score()
{

}

Score::~Score()
{
  this->writeScores();
}

void    Score::saveScore(Tuple<std::string, int> score)
{
  this->m_scoreMap.push_back(score);
  std::sort(this->m_scoreMap.begin(), this->m_scoreMap.end(), sort_vector);
}

void    Score::saveScore(std::string const& name, int score)
{
  Tuple<std::string, int> toSave;

  toSave.a = name;
  toSave.b = score;
  this->saveScore(toSave);
}

std::vector<Tuple<std::string, int>> const& Score::getScores() const
{
  return (this->m_scoreMap);
}

void    Score::loadScoreFile(std::string const& path)
{
  std::ifstream file;
  std::string   line;

  this->filePath = path;
  file.open(path.c_str());
  if (file.is_open())
  {
    while (std::getline(file, line))
    {
      std::string   name;
      std::string   score_str;
      size_t pos = line.find(":");
      Tuple<std::string, int> item;

      if (pos != std::string::npos)
      {
        name = line.substr(0, pos);
        score_str = line.substr(pos + 1);
        if (!name.empty())
        {
          item.a = name;
          item.b = std::atoi(score_str.c_str());
          this->m_scoreMap.push_back(item);
        }
      }
    }
    file.close();
  }
  else
    std::cout << "Unable to open score file" << std::endl;
  std::sort(this->m_scoreMap.begin(), this->m_scoreMap.end(), sort_vector);
}

void    Score::writeScores()
{
  std::ofstream  file;

  file.open(filePath.c_str());
  for (auto it = this->m_scoreMap.begin(); it < this->m_scoreMap.end(); it++)
  {
    file << (*it).a << ":" << (*it).b << std::endl;
  }
  file.close();
}
