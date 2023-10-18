for i in {0..10}; do
  if test -f "./data/level7_$i.in"; then
    ./bin/build < "./data/level7_$i.in" > "./data/level7_$i.out"
    echo "done level $i"
  fi
done

./bin/build < "./data/level7_example.in" > "./data/level7_example.out"