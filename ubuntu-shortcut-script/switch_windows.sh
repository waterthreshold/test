#!/bin/sh
wmctrl -R $(wmctrl -l | cut -c $((${#HOSTNAME}+16))- | dmenu -p "Window")
