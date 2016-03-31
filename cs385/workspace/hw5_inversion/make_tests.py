str1 = ''#0->100000
str2 = ''#100000->0
for x in range(100000+1):
    str1 += str(x) + ' '
    str2 += str(100000-x) + ' '

inv_sum=0
for x in range(100000+1):
    inv_sum += x

test1 = 'run_test_args "slow" "' + str1[:-1] + '" "Enter sequence of integers, each followed by a space: Number of inversions: 0"'
test2 = 'run_test_args "slow" "' + str2[:-1] + '" "Enter sequence of integers, each followed by a space: Number of inversions: ' + str(inv_sum) + '"'

print test1
print test2
