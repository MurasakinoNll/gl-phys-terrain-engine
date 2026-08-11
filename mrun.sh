#!/bin/bash
make 2>&1 | tee lastcompile.txt
status=${PIPESTATUS[0]}
[ $status -eq 0 ] && prime-run ./bins/engine && echo "build success" || echo "build failed"
