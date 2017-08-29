g++ *.cpp -o Lab5
echo `./Lab5 <input1.txt> output1.txt 2>&1`
echo `./Lab5 <input2.txt> output2.txt 2>&1`
echo `./Lab5 <input3.txt> output3.txt 2>&1`
echo `./Lab5 <input4.txt> output4.txt 2>&1`
echo `./Lab5 <input5.txt> output5.txt 2>&1`

echo `diff output1.txt outputRefrence1.txt 2>&1` 
echo `diff output2.txt outputRefrence2.txt 2>&1` 
echo `diff output3.txt outputRefrence3.txt 2>&1` 
echo `diff output4.txt outputRefrence4.txt 2>&1` 
echo `diff output5.txt outputRefrence5.txt 2>&1`
