#! /bin/bash

dir="change"

if [ ! -d $dir ]; then
    mkdir $dir 
fi 

for name in `ls`
    do
        if [ $name == $dir -o $name == 'gb2312_to_utf8.sh' ]; then
            continue
        fi
        iconv -f gb2312 -t utf8 $name > $dir/$name
    done

cd $dir

sed -i "s/&nbsp/ /g" `grep -rl \&nbsp`
cd -
