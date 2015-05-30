#! /bin/bash

dtc -O dtb -o BLACKLIB-SPI0-00A0.dtbo -b 0 -@ BLACKLIB-SPI0-00A0.dts

dtc -O dtb -o BLACKLIB-SPI1-00A0.dtbo -b 0 -@ BLACKLIB-SPI1-00A0.dts

cp -r BLACKLIB-SPI0-00A0.dtbo BLACKLIB-SPI1-00A0.dtbo /lib/firmware

rm -rf BLACKLIB-SPI*
