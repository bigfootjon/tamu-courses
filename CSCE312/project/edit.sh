#!/bin/sh
vim $1.ys && ./sim/misc/yas $1.ys && ./sim/seq/ssim $1.yo
