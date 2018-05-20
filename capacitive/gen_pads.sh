#!/bin/sh

python padgen/gen_tx_pads.py > capacitive.pretty/TX_PADS.kicad_mod
python padgen/gen_rx_pad.py > capacitive.pretty/RX_PAD.kicad_mod
