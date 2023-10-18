for i in {0..10}; do
  if test -f "./data/level5_$i.in"; then
    ./bin/build < "./data/level5_$i.in" > "./data/level5_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level5_example.in" > "./data/level5_example.out"