#!/usr/bin/env bash
mkdir -p logs
for f in inputs/*.json; do
  name=$(basename "$f" .json)
  ./driver "$f" > "logs/$name.log" 2>&1
  printf '%-28s exit=%d\n' "$name" "$?"
done
echo
echo "Output saved in logs/"
