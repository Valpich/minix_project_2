#!/bin/sh
cp /usr/src/servers/pm/project_2_syst_call.c /usr/src/project_2/project_2_syst_call.c
cc main.c project_2_syst_call -o main
./main
