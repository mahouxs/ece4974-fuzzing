#!/usr/bin/env bash
set -e
SAN="-fsanitize=address,undefined -fno-sanitize-recover=all"
for d in driver driver_v1 driver_v2; do
  clang $SAN -g -O1 -Wall -I. "$d.c" -o "$d"
  echo "built $d"
done
