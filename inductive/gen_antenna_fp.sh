#!/bin/bash

python gen_antenna_0_45.py > inductive.pretty/antenna_0_45.kicad_mod
python gen_antenna_45_135.py > inductive.pretty/antenna_45_135.kicad_mod
python gen_antenna_135_180.py > inductive.pretty/antenna_135_180.kicad_mod

