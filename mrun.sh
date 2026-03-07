#!/bin/bash
make
status=$?
[ $status -eq 0 ] && prime-run ./bins/engine && echo "build success" || echo "build failed"
