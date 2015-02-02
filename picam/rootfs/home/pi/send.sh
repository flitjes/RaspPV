raspivid -w 800 -h 480 -fps 20 -n -pf baseline -ex auto -o - -t 0 | \
gst-launch-0.10 -v fdsrc !  h264parse ! rtph264pay config-interval=10 pt=96 ! udpsink host=192.168.1.255 port=9000 
