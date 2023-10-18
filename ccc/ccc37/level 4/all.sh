for i in {0..10}; do
  if test -f "./data/level4_$i.in"; then
    ./bin/build < "./data/level4_$i.in" > "./data/level4_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level4_example.in" > "./data/level4_example.out"