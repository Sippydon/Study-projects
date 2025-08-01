cd cat/ && bash test_func_cat.sh &> ../test_integrate.txt && cd ../
cd grep/ && bash test_func_grep.sh &>> ../test_integrate.txt && cd ../

FAIL=$(grep 'FAIL:' test_integrate.txt)

arr=($(echo $FAIL | tr " " "\n"))

if [[ ${arr[1]} == "0" && ${arr[3]} == "0" ]]; then
    echo "succeeded integration tests"
  else
    echo "failed integration tests"
    exit 1;
fi