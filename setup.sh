#!/bin/bash

echo "[APT] Installing dependencies ..."
sudo apt install gcc-avr avr-libc avrdude build-essential minicom git
echo "[APT] Done!"

while true; do
    read -p "Install minicom configs? " yn
    case $yn in
        [Yy]* ) profiles=yes; break;;
        [Nn]* ) profiles=no; break;;
        * ) echo "Please answer yes or no.";;
    esac
done

if [ $profiles == "yes" ]; then
    echo "Installing minicom profiles ..."
    cp minirc.ttyUSB0 /home/$USER/.minirc.ttyUSB0
    cp minirc.ttyUSB1 /home/$USER/.minirc.ttyUSB1
fi

echo "[GIT] Fetchin RIOT dependency ..."
git submodule init
git submodule update
echo "[GIT] Done."

echo "[RIOT] Installing virtual interfaces ..."
sudo ./RIOT/dist/tools/tapsetup/tapsetup
echo "[RIOT] Done!"
