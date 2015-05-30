If you want to use spi, you must use custom device tree overlays.
For this reason i wrote setup scripts and custom device tree overlays.
You must run one of these scripts for using spi feature of Beaglebone
Black. You can do this with two ways.

### FROM HOST PC

- If you are doing these steps from your host pc, you must run 
"setup_from_host" script. Before run this, you must give executable 
permission. 

- You can do this with this command: "chmod +x setup_from_host"

- "BLACKLIB-SPI0-00A0.dts", "BLACKLIB-SPI1-00A0.dts" and "setup_from_host" files
must be located in this directory.

- After do that you must run the script with this command: "./setup_from_host"

- When you run the script, it will ask you Beaglebone Black's root user's
password two times. This is required for executing "scp" and "ssh" command.

- That's all.



### INSIDE FROM BEAGLEBONE BLACK

- If you are doing these steps from your BBB, you must connect to BBB and
change your current directory to script's directory with "cd" command. 

- "BLACKLIB-SPI0-00A0.dts", "BLACKLIB-SPI1-00A0.dts" and "setup_from_BBB" files
must be located in this directory.

- Before run this script, you must give executable permission. You can do this 
with this command: "chmod +x setup_from_BBB"

- After do that you must run the script with this command: "./setup_from_BBB"

- That's all. 

