for i in {0..10}; do
  if test -f "./data/level1_$i.in"; then
    ./bin/build < "./data/level1_$i.in" > "./data/level1_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level1_example.in" > "./data/level1_example.out"