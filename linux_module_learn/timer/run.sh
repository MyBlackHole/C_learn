make

sudo dmesg -w

sudo insmod main.ko


# [277953.977790] Hello TaXue
# [277955.000509] hello timer count=0
# [277955.016512] hello timer count=1
# [277955.044502] hello timer count=2
# [277955.080512] hello timer count=3
# [277955.128528] hello timer count=4
# [277955.188533] hello timer count=5
# [277955.256719] hello timer count=6
# [277955.332521] hello timer count=7
# [277955.416738] hello timer count=8
# [277955.512525] hello timer count=9
# [277955.616732] hello timer count=10
# [277955.732724] hello timer count=11
# [277955.860730] hello timer count=12
# .....
# done

sudo rmmod main


# [278005.867020] platform driver exit!
