for i in {0..10}; do
  if test -f "./data/level2_$i.in"; then
    ./bin/build < "./data/level2_$i.in" > "./data/level2_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level2_example.in" > "./data/level2_example.out"