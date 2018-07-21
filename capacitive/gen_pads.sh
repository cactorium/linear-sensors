#!/bin/sh

SCALE_LENGTH=320.00

python padgen/gen_tx_pads.py > capacitive.pretty/TX_PADS.kicad_mod
python padgen/gen_rx_pad.py > capacitive.pretty/RX_PAD.kicad_mod

python padgen/gen_scales.py ${SCALE_LENGTH} > capacitive.pretty/Capacitive_Scales${SCALE_LENGTH}.kicad_mod

python padgen/gen_scale_drill_left.py > capacitive.pretty/Scale_Drill_Left.kicad_mod
python padgen/gen_scale_drill_right.py > capacitive.pretty/Scale_Drill_Right.kicad_mod

python padgen/gen_slide_drill_left.py > capacitive.pretty/Slide_Drill_Left.kicad_mod
python padgen/gen_slide_drill_right.py > capacitive.pretty/Slide_Drill_Right.kicad_mod

python padgen/gen_scale_outline.py > capacitive.pretty/Scale_Outline.kicad_mod
