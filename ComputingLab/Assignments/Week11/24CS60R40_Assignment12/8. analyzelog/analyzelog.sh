#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Incorrect number of arguments."
    echo "Usage: $0 <log_file_path> <time_window_in_minutes>"
    exit 1
fi

LOG_FILE="$1"
TIME_WINDOW="$2"

if ! [[ "$TIME_WINDOW" =~ ^[0-9]+$ ]]; then
    echo "Time window must be a positive integer."
    exit 1
fi

if [ ! -f "$LOG_FILE" ]; then
    echo "Log file '$LOG_FILE' not found."
    exit 1
fi





TIME_WINDOW_SEC=$((TIME_WINDOW * 60))

entries=()

declare -A ipAddressCount

while IFS= read -r line; do

    timestamp=$(echo "$line" | awk '{print $1, $2}' | tr -d '[]')
    ipAddress=$(echo "$line" | awk '{print $3}')
    
 
    timeStamp=$(date -d "$timestamp" +%s)
    
   
    entries+=("$timeStamp|$ipAddress")

done < "$LOG_FILE"


maxCount=0
startTime=0
endTime=0
busiestIpAddressCount=()

for entry in "${entries[@]}"; do
    currentTime=$(echo "$entry" | cut -d '|' -f 1)
    
  
    declare -A windowIpAddressCount
    count=0
    
 
    for e in "${entries[@]}"; do
        entry_time=$(echo "$e" | cut -d '|' -f 1)
        entry_ip=$(echo "$e" | cut -d '|' -f 2)

     
        if (( entry_time >= currentTime && entry_time < currentTime + TIME_WINDOW_SEC )); then
            ((count++))
            windowIpAddressCount["$entry_ip"]=$((windowIpAddressCount["$entry_ip"] + 1))
        fi
    done

    if (( count > maxCount )); then
        maxCount=$count
        startTime=$currentTime
        endTime=$((currentTime + TIME_WINDOW_SEC))
        busiestIpAddressCount=()
        
      
        for ip in "${!windowIpAddressCount[@]}"; do
            busiestIpAddressCount+=("$ip ${windowIpAddressCount[$ip]}")
        done
    fi
done


if (( maxCount > 0 )); then
    echo "Start Time: $(date -d @"$startTime" '+%Y-%m-%d %H:%M:%S')"
    echo "End Time: $(date -d @"$endTime" '+%Y-%m-%d %H:%M:%S')"
    echo "No of Entries: $maxCount"
    
   
    echo "Top 3 IPs in window:"
    if [ ${#busiestIpAddressCount[@]} -gt 0 ]; then
      
        printf '%s\n' "${busiestIpAddressCount[@]}" | sort -k2,2nr | head -n 3 | while read -r line; do
            echo "$line"
        done
    else
        echo "No IPs found."
    fi
else
    echo "No entries found in the log."
fi
