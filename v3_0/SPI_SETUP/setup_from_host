#! /bin/bash

scp BLACKLIB-SPI0-00A0.dts BLACKLIB-SPI1-00A0.dts root@192.168.7.2:/tmp

ssh root@192.168.7.2 '
cd /tmp

dtc -O dtb -o BLACKLIB-SPI0-00A0.dtbo -b 0 -@ BLACKLIB-SPI0-00A0.dts

dtc -O dtb -o BLACKLIB-SPI1-00A0.dtbo -b 0 -@ BLACKLIB-SPI1-00A0.dts

cp -r BLACKLIB-SPI0-00A0.dtbo BLACKLIB-SPI1-00A0.dtbo /lib/firmware

rm -rf BLACKLIB-SPI*
'
