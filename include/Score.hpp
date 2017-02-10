//
// Score.hpp for cpp_arcade in /home/archie/workspace/C++/cpp_arcade/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Fri Mar 18 09:43:49 2016 Corentin Descamps
// Last update Fri Mar 18 12:58:16 2016 Corentin Descamps
//

#ifndef   SCORE_HPP_
# define  SCORE_HPP_

# include <iostream>
# include <fstream>
# include <vector>
# include <algorithm>
# include "Tuple.hpp"

class Score
{
public:
  Score();
  ~Score();
  void  loadScoreFile(std::string const& path);
  void  saveScore(Tuple<std::string, int> score);
  void  saveScore(std::string const& name, int score);
  void  writeScores();
  std::vector<Tuple<std::string, int>> const& getScores() const;

private:
  std::vector<Tuple<std::string, int>>  m_scoreMap;
  std::string     filePath;
};

#endif    /* SCORE_HPP_ */
