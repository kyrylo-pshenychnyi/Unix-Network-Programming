for i in `ipcs -q |awk  '{print $2}' | tail -n +4` 
do 
	echo $i
	ipcrm -q $i 
done
