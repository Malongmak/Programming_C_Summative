#!/bin/bash

LOG_FILE="system_performance.log"

echo "Timestamp, CPU Usage (%), Memory Usage (%)" > "$LOG_FILE"

while true; do
    TIMESTAMP=$(date +"%Y-%m-%d %H:%M:%S")
    
    
    CPU_USAGE=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
    
    
    MEMORY_USAGE=$(free | grep Mem | awk '{print $3/$2 * 100.0}')
    
    if [ $? -ne 0 ]; then
        echo "Error getting system performance data"
        exit 1
    fi

    echo "$TIMESTAMP, $CPU_USAGE, $MEMORY_USAGE" >> "$LOG_FILE"
    
    sleep 2
done
