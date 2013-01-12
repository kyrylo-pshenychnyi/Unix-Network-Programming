for i in `ipcs -q |awk  '{print $2}'` 
do 
	#echo $i
	ipcrm -q $i 
done
