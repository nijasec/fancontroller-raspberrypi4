#! /bin/sh

### BEGIN INIT INFO
# Provides:          fan.o
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
### END INIT INFO

# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo "Starting fan.o"
    /usr/local/bin/fan.o &
    ;;
  stop)
    echo "Stopping fan.o"
    pkill -f /usr/local/bin/fan.o
    ;;
  *)
    echo "Usage: /etc/init.d/fancontrol.sh {start|stop}"
    exit 1
    ;;
esac

exit 0
