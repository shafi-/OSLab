for i in {1,2,4,8,16,32,64,128,256}
do
    for j in {1,2,4,8,16,32,64,128,256}
    do
        if [ "$i" -gt "$j" ];
        then
            continue
        fi
        c='_'
        ./memoryManagementUnit.out 0 $i $j 100000 > "$i$c$j".txt 
    done
done
