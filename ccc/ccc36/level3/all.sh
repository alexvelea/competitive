for i in {0..10}; do
  if test -f "./data/level3_$i.in"; then
    ./bin/build < "./data/level3_$i.in" > "./data/level3_$i.out"
    echo "done level $i"
  fi
done
