for i in {0..10}; do
  if test -f "./data/level6_$i.in"; then
    ./bin/build < "./data/level6_$i.in" > "./data/level6_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level6_example.in" > "./data/level6_example.out"