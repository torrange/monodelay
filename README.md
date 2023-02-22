# Monodelay

## monodelay.lv2

Monodelay is a simple LV2 plugin implementing a mono Haas-effect delay.
This plugin should build on Linux, Windows and Mac, however has only been tested under Ubuntu 22.04 with [Reaper v6.75](https://reaper.fm)

## Building from source (Ubuntu 22.04)

`monodelay.lv2` requires the following tools to compile from source
- LV2 SDK
- gnu-make
- a c-compiler

The quickest way to get started on Ubuntu 22.04 is to install the `build-essential` and `lv2-dev` packages
```
sudo apt update
sudo apt install build-essential lv2-dev
```

After these packages have been installed, navigate to the project root
```
make all
sudo make install
```

The `monodelay.lv2` plugin should be installed to `/usr/local/lib/lv2/monodelay.lv2`.


For more information on the LV2 plugin format please visit https://lv2plug.in

