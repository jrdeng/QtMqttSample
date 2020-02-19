# Qt MQTT sample

show how to use qmmqtt ( https://github.com/qt/qtmqtt )

this sample is tested on Windows 10 with Qt 5.12.7(VS2017 x64).

## dependencies

- build qtmqtt and put it in project (libs prebuilt with msvc2017 and msvc2017_64 for Qt 5.12.7 are attached)

## build & run

just use Qt Creator to open this project, update *.pro file if you add new qtmqtt libs(for other platforms or toolchains).

then build & run.



## how to build qtmqtt

    git clone git@github.com:qt/qtmqtt.git
    # checkout tag for specified version
    mkdir build
    cd build
    qmake .. # qmake need to be in PATH, and for Windows, "VSxxxx [x64] Native Tools Command Prompt" can be use to load VS env.
    make # or nmake for Windows
    