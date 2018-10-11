for filename in ./test/*.txt; do
    echo "$filename"
    ./a.out < "$filename"
done
