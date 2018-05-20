#!/bin/sh

SCALE_LENGTH=200.00

python padgen/gen_tx_pads.py > capacitive.pretty/TX_PADS.kicad_mod
python padgen/gen_rx_pad.py > capacitive.pretty/RX_PAD.kicad_mod
python padgen/gen_scales.py ${SCALE_LENGTH} > capacitive.pretty/CAP_SCALES_${SCALE_LENGTH}.kicad_mod
