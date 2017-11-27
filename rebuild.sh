#!/bin/bash
make clean && make && arm-elf-gdb interrupts.elf
