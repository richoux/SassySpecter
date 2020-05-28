/*
 * SassySpecter is an AI bot playing to both StarCraft: Brood War and StarCraft II, with the same code.
 * It uses GHOST, a Constraint Programming toolkit, to design and solve combinatorial problems for
 * all decision-making behaviors. Please visit https://github.com/richoux/SassySpecter for further information.
 *
 * Copyright (C) 2020-2020 Florian Richoux
 *
 * This file is part of SassySpecter.
 * SassySpecter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * SassySpecter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with SassySpecter. If not, see http://www.gnu.org/licenses/.
 */

#pragma once
#include "TechTree.h"

class SassySpecterBot;

class TechTreeManager
{
  SassySpecterBot& bot;

public:
  TechTreeManager( SassySpecterBot& bot );
  void onStart();
};
